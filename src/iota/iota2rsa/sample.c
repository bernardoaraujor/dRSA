#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dopenssl/rsa.h>
#include <dopenssl/rand.h>

#include "iota/iota2rsa/iota2rsa.h"

int gen_rsa(RSA **rsa, rsa_seed_t *rsa_seed)
{

  *rsa = (RSA*) malloc(sizeof(RSA));
  if ((*rsa = dRSA_deduce_privatekey(rsa_seed->bits, rsa_seed->seed)) == NULL)
  {
    printf("[error] unable to generate the RSA key pair\n");
    return (1);
  }

}

int main(int argc, char **argv)
{
  unsigned char* iota_seed = "DEJUXV9ZQMIEXTWJJHJPLAWMOEKGAYDNALKSMCLG9AGPR9LCKHMLNZVCRFNFEPMGOBOYYIKJNYWSAVPAI";
  unsigned int const length = strlen(iota_seed);

  rsa_seed_t rsa_seed;
  if (!rsa_seed_init(&rsa_seed, 2048)){
      printf("error: rsa_seed not initialized");
      return 0;
  }

  if (!iota2rsa_set_rsa_seed(iota_seed, &rsa_seed)){
      printf("error: iota2rsa conversion unsuccessfull");
      return 0;
  }

  /** forget iota_seed **/
  iota_seed = NULL;

  /* Initialize the deterministic random generator */
  if (dRAND_init() != 1)
  {
      printf("[error] unable to initialize the random generator\n");
      return (1);
  }

  RSA* rsa_1;
  RSA* rsa_2;

  /** generate rsa_1 and rsa_2 from the same rsa_seed **/
  gen_rsa(&rsa_1, &rsa_seed);
  gen_rsa(&rsa_2, &rsa_seed);

  /** forget rsa_seed **/
  rsa_seed_destroy(&rsa_seed);

  char rsa_key_1;
  char rsa_key_2;

  RSA_print_fp(stdout, rsa_1, 0);
  RSA_print_fp(stdout, rsa_1, 0);

  /** check if rsa_1 and rsa_2 are identical **/
  if (0 != memcmp(rsa_1, rsa_2, sizeof(RSA))){
      printf("error: rsa_1 and rsa_2 are different");
      return 0;
  }


    free(rsa_1);
  free(rsa_2);

  /* Clean the resources */
  if (dRAND_clean() != 1)
  {
    printf("[error] unable to clean the random generator\n");
    return (1);
  }

  return (0);
}
