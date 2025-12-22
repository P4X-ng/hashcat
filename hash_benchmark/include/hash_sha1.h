/**
 * Hash Benchmark Library - SHA1 Implementation
 * Extracted and adapted from hashcat
 * License: MIT
 */

#ifndef HASH_SHA1_H
#define HASH_SHA1_H

#include "hash_types.h"

// SHA1 constants
#define SHA1_DIGEST_SIZE 20
#define SHA1_BLOCK_SIZE  64

// SHA1 initial values
#define SHA1C00 0x67452301u
#define SHA1C01 0xefcdab89u
#define SHA1C02 0x98badcfeu
#define SHA1C03 0x10325476u
#define SHA1C04 0xc3d2e1f0u

// SHA1 round constants
#define SHA1C05 0x5a827999u
#define SHA1C06 0x6ed9eba1u
#define SHA1C07 0x8f1bbcdcu
#define SHA1C08 0xca62c1d6u

// SHA1 auxiliary functions
#define SHA1_F0(x,y,z) ((z) ^ ((x) & ((y) ^ (z))))
#define SHA1_F1(x,y,z) ((x) ^ (y) ^ (z))
#define SHA1_F2(x,y,z) (((x) & (y)) | ((z) & ((x) | (y))))
#define SHA1_F3(x,y,z) ((x) ^ (y) ^ (z))

// SHA1 step macro
#define SHA1_STEP(f,a,b,c,d,e,x,K) \
{ \
  e += hc_rotl32_S(a, 5) + f(b, c, d) + x + K; \
  b = hc_rotl32_S(b, 30); \
}

// SHA1 context structure
typedef struct {
  u32 h[5];
  u32 w0[4];
  u32 w1[4];
  u32 w2[4];
  u32 w3[4];
  int len;
} sha1_ctx_t;

// Function declarations
void sha1_init(sha1_ctx_t *ctx);
void sha1_update_64(sha1_ctx_t *ctx, const u32 *w0, const u32 *w1, const u32 *w2, const u32 *w3, const int len);
void sha1_update(sha1_ctx_t *ctx, const u8 *input, const int len);
void sha1_final(sha1_ctx_t *ctx, u8 *digest);
void sha1_transform(const u32 *w0, const u32 *w1, const u32 *w2, const u32 *w3, u32 *digest);

// Convenience function
void sha1_hash(const u8 *input, int len, u8 *digest);

#endif // HASH_SHA1_H