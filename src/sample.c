#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dopenssl/rsa.h>
#include <dopenssl/rand.h>

#include "iota2rsa/iota2rsa.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("usage: %s [iota_seed]\n", argv[0]);
    return(1);
  }

  unsigned char* iota_seed = argv[1];
  unsigned int const length = strlen(iota_seed);
  if(length != 81){
    printf("[error] IOTA seeds are 81 chars long.\n");
    return (1);
  }

  unsigned int const rsa_bits = 2048;
  unsigned char* rsa_seed;

  if (!iota2rsa(iota_seed, rsa_seed, rsa_bits))
      return 0;

  /* Initialize the deterministic random generator */
  if (dRAND_init() != 1)
  {
    printf("[error] unable to initialize the random generator\n");
    return (1);
  }

  /* Generate the RSA key */
  RSA* rsa = NULL;

  if ((rsa = dRSA_deduce_privatekey(rsa_bits, rsa_seed)) == NULL)
  {
    printf("[error] unable to generate the RSA key pair\n");
    return (1);
  }

  /* Display the RSA components */
  RSA_print_fp(stdout, rsa, 0);

  /* Clean the resources */
  if (dRAND_clean() != 1)
  {
    printf("[error] unable to clean the random generator\n");
    return (1);
  }

  return (0);
}
