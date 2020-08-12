#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dopenssl/rsa.h>
#include <dopenssl/rand.h>

#include "iota2rsa/iota2rsa.h"

int genrsa(RSA* rsa, unsigned int rsa_bits, unsigned char* rsa_seed)
{
  /* Initialize the deterministic random generator */
  if (dRAND_init() != 1)
  {
    printf("[error] unable to initialize the random generator\n");
    return (1);
  }

  if ((rsa = dRSA_deduce_privatekey(rsa_bits, rsa_seed)) == NULL)
  {
    printf("[error] unable to generate the RSA key pair\n");
    return (1);
  }
}

int main(int argc, char **argv)
{
  unsigned char* const iota_seed = "DEJUXV9ZQMIEXTWJJHJPLAWMOEKGAYDNALKSMCLG9AGPR9LCKHMLNZVCRFNFEPMGOBOYYIKJNYWSAVPAI";
  unsigned int const length = strlen(iota_seed);

  rsa_seed_t *rsa_seed;
  if (!rsa_seed_init(&rsa_seed, 2048)){
      printf("error: rsa_seed not initialized");
      return 0;
  }

  if (!seed_iota2rsa(iota_seed, &rsa_seed)){
      printf("error: iota2rsa conversion unsuccessfull");
  }
      return 0;

  RSA* rsa = NULL;
  genrsa(rsa, rsa_seed->bits, rsa_seed->seed);

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
