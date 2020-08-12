#include "common/trinary/tryte.h"
#include "rsa.h"

/**
 * @brief convert iota_seed to rsa_seed
 *
 * RSA keypairs are generated from a PRNG with rsa_seed as input.
 * Since we want RSA keypairs tied to the iota_seed, we need a way
 * to convert iota_seed to rsa_seed.
 *
 * rsa_seed is a 256-byte binary array
 * iota_seed is a string of 81-tryte (48 bytes) ternary array
 *
 * rsa_seed is much bigger, so we repeat iota_seed contents x times plus one truncated.
 *
 * @param iota_seed pointer to IOTA seed (input)
 * @param rsa_seed pointer to RSA seed (output)
 * @param rsa_bits total rsa_seed bits
 *
 * @return 0 for error, 1 for success
 */
int iota2rsa_set_rsa_seed(tryte_t *iota_seed, rsa_seed_t *rsa_seed);