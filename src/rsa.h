/*
 * Copyright (c) 2013, infinit.io
 *
 * This software is provided "as is" without warranty of any kind,
 * either expressed or implied, including but not limited to the
 * implied warranties of fitness for a particular purpose.
 *
 * See the LICENSE file for more information on the terms and
 * conditions.
 */

#ifndef DOPENSSL_RSA_H
# define DOPENSSL_RSA_H

# include <openssl/rsa.h>

/**
 * @brief struct representation of rsa_seed
 */
typedef struct{
    unsigned char* seed;
    unsigned int seed_len;
    unsigned int bits;
} rsa_seed_t;

/**
 * @brief rsa_seed_t initializer
 *
 * @param rsa_seed pointer to rsa_seed_t
 * @param rsa_bits rsa bits
 * @return 0 for error, 1 for success
 */
int rsa_seed_init(rsa_seed_t *rsa_seed, unsigned int rsa_bits);

/**
 * @brief rsa_seed_t destroyer
 * @param rsa_seed  pointer to rsa_seed_t
 * @return 0 for error, 1 for success
 */
int rsa_seed_destroy(rsa_seed_t *rsa_seed);

/* Fill the public key of the given _rsa_ with the modulus _N_ and deduce the
   exponent with a deterministic PNRG seeded with the content provided. */
RSA *dRSA_deduce_publickey(BIGNUM *N,
                           const unsigned char *seed, size_t seed_length);
/* Deduce the whole private key _rsa_ of the given size in _bits_ by relying on
   a deterministic PNRG seeded with the content provided. */
RSA *dRSA_deduce_privatekey(int bits,
                            const unsigned char *seed);
/* Compare the public part of the two given RSA keys. */
int dRSA_cmp_publickey(RSA *a, RSA *b);
/* Compare the private part of the two given RSA keys. */
int dRSA_cmp_privatekey(RSA *a, RSA *b);
/* Display on the standard output the various numbers composing an RSA key. */
int dRSA_print(RSA *rsa);

#endif
