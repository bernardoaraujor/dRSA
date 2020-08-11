#include "iota2rsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iota2rsa(unsigned char *iota_seed, unsigned char* rsa_seed, unsigned int rsa_bits){

    unsigned int const rsa_seed_len = rsa_bits / 8;
    unsigned int const iota_seed_len = strlen(iota_seed);

    unsigned int const occurences = rsa_seed_len / iota_seed_len + 1;
    unsigned int const tmp_seed_len = occurences * iota_seed_len + 1;

    unsigned char *tmp_seed = malloc(tmp_seed_len);
    memset(tmp_seed, 0x0, tmp_seed_len);

    /* concatenate iota_seed repetitions into tmp_seed */
    unsigned int i;
    for (i = 0; i < occurences; i++)
        strncpy(tmp_seed + (i * iota_seed_len), iota_seed, iota_seed_len);
    /* tmp_seed is slightly bigger than rsa_seed_len */

    /* so we truncate tmp_seed into rsa_seed */
    rsa_seed = malloc(rsa_seed_len);
    for (i = 0; i < rsa_seed_len; i++)
        strncpy(rsa_seed, tmp_seed, rsa_seed_len);

    /* we don't need tmp_seed anymore */
    free(tmp_seed);

    return 1;
}
