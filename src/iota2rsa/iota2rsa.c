#include "iota2rsa.h"
#include "rsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seed_iota2rsa(tryte_t *iota_seed, rsa_seed_t **rsa_seed){

    if ((*rsa_seed)->bits != 2048){
      printf("error: only RSA 2048 is supported.");
      return 0;
    }

    unsigned int const iota_seed_len = strlen(iota_seed);
    if (!is_trytes(iota_seed, iota_seed_len)){
        printf("error: iota_seed is not valid trytes.");
        return 0;
    }

    for (int i = 0; i < (*rsa_seed)->seed_len; i++)
        (*rsa_seed)->seed[i] = iota_seed[i % iota_seed_len];

    return 1;
}
