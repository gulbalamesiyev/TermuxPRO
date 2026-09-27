
/*
 * SHA-1 in C
 * By Steve Reid <steve@edmweb.com>
 * 100% Public Domain
 */

#ifndef _SHA1_H
#define _SHA1_H

#include <sys/types.h>
#include <stdint.h>

#define	SHA1_BLOCK_LENGTH		64
#define	SHA1_DIGEST_LENGTH		20

typedef struct {
    uint32_t state[5];
    uint64_t count;
    uint8_t buffer[SHA1_BLOCK_LENGTH];
} SHA1_CTX;

void SHA1Init(SHA1_CTX *);
void SHA1Pad(SHA1_CTX *);
void SHA1Transform(uint32_t [5], const uint8_t [SHA1_BLOCK_LENGTH]);
void SHA1Update(SHA1_CTX *, const uint8_t *, size_t);
void SHA1Final(uint8_t [SHA1_DIGEST_LENGTH], SHA1_CTX *);

#endif /* _SHA1_H */

