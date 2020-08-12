#include "iota2rsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/trinary/tryte.h"

int iota2rsa(unsigned char *iota_seed, unsigned char* rsa_seed, unsigned int rsa_bits){

    unsigned int const iota_seed_len = strlen(iota_seed);
    if (!is_trytes(iota_seed, iota_seed_len)){
        printf("error: iota_seed is not valid trytes.");
        return 0;
    }

    unsigned int const rsa_seed_len = rsa_bits / 8;

    rsa_seed = malloc(rsa_seed_len);
    memset(rsa_seed, 0x0, rsa_seed_len);
    for (int i = 0; i < rsa_seed_len; i++)
        rsa_seed[i] = iota_seed[i % iota_seed_len];

    return 1;
}
