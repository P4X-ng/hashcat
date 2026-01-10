/**
 * Hash Benchmark Library - MD5 Implementation
 * Extracted and adapted from hashcat
 * License: MIT
 */

#ifndef HASH_MD5_H
#define HASH_MD5_H

#include "hash_types.h"

// MD5 constants
#define MD5_DIGEST_SIZE 16
#define MD5_BLOCK_SIZE  64

// MD5 round constants
#define MD5C00 0x67452301u
#define MD5C01 0xefcdab89u
#define MD5C02 0x98badcfeu
#define MD5C03 0x10325476u

#define MD5C04 0xd76aa478u
#define MD5C05 0xe8c7b756u
#define MD5C06 0x242070dbu
#define MD5C07 0xc1bdceeeu
#define MD5C08 0xf57c0fafu
#define MD5C09 0x4787c62au
#define MD5C0a 0xa8304613u
#define MD5C0b 0xfd469501u
#define MD5C0c 0x698098d8u
#define MD5C0d 0x8b44f7afu
#define MD5C0e 0xffff5bb1u
#define MD5C0f 0x895cd7beu

#define MD5C10 0x6b901122u
#define MD5C11 0xfd987193u
#define MD5C12 0xa679438eu
#define MD5C13 0x49b40821u
#define MD5C14 0xf61e2562u
#define MD5C15 0xc040b340u
#define MD5C16 0x265e5a51u
#define MD5C17 0xe9b6c7aau
#define MD5C18 0xd62f105du
#define MD5C19 0x02441453u
#define MD5C1a 0xd8a1e681u
#define MD5C1b 0xe7d3fbc8u
#define MD5C1c 0x21e1cde6u
#define MD5C1d 0xc33707d6u
#define MD5C1e 0xf4d50d87u
#define MD5C1f 0x455a14edu

#define MD5C20 0xa9e3e905u
#define MD5C21 0xfcefa3f8u
#define MD5C22 0x676f02d9u
#define MD5C23 0x8d2a4c8au
#define MD5C24 0xfffa3942u
#define MD5C25 0x8771f681u
#define MD5C26 0x6d9d6122u
#define MD5C27 0xfde5380cu
#define MD5C28 0xa4beea44u
#define MD5C29 0x4bdecfa9u
#define MD5C2a 0xf6bb4b60u
#define MD5C2b 0xbebfbc70u
#define MD5C2c 0x289b7ec6u
#define MD5C2d 0xeaa127fau
#define MD5C2e 0xd4ef3085u
#define MD5C2f 0x04881d05u

#define MD5C30 0xd9d4d039u
#define MD5C31 0xe6db99e5u
#define MD5C32 0x1fa27cf8u
#define MD5C33 0xc4ac5665u
#define MD5C34 0xf4292244u
#define MD5C35 0x432aff97u
#define MD5C36 0xab9423a7u
#define MD5C37 0xfc93a039u
#define MD5C38 0x655b59c3u
#define MD5C39 0x8f0ccc92u
#define MD5C3a 0xffeff47du
#define MD5C3b 0x85845dd1u
#define MD5C3c 0x6fa87e4fu
#define MD5C3d 0xfe2ce6e0u
#define MD5C3e 0xa3014314u
#define MD5C3f 0x4e0811a1u

#define MD5C40 0xf7537e82u
#define MD5C41 0xbd3af235u
#define MD5C42 0x2ad7d2bbu
#define MD5C43 0xeb86d391u

// MD5 shift amounts
#define MD5S00  7
#define MD5S01 12
#define MD5S02 17
#define MD5S03 22
#define MD5S10  5
#define MD5S11  9
#define MD5S12 14
#define MD5S13 20
#define MD5S20  4
#define MD5S21 11
#define MD5S22 16
#define MD5S23 23
#define MD5S30  6
#define MD5S31 10
#define MD5S32 15
#define MD5S33 21

// MD5 auxiliary functions
#define MD5_F(x,y,z) ((z) ^ ((x) & ((y) ^ (z))))
#define MD5_G(x,y,z) ((y) ^ ((z) & ((x) ^ (y))))
#define MD5_H(x,y,z) ((x) ^ (y) ^ (z))
#define MD5_I(x,y,z) ((y) ^ ((x) | ~(z)))

// MD5 step macro
#define MD5_STEP(f,a,b,c,d,x,K,s) \
{ \
  a += K; \
  a = hc_add3_S(a, x, f(b, c, d)); \
  a = hc_rotl32_S(a, s); \
  a += b; \
}

// MD5 context structure
typedef struct {
  u32 h[4];
  u32 w0[4];
  u32 w1[4];
  u32 w2[4];
  u32 w3[4];
  int len;
} md5_ctx_t;

// Function declarations
void md5_init(md5_ctx_t *ctx);
void md5_update_64(md5_ctx_t *ctx, const u32 *w0, const u32 *w1, const u32 *w2, const u32 *w3, const int len);
void md5_update(md5_ctx_t *ctx, const u8 *input, const int len);
void md5_final(md5_ctx_t *ctx, u8 *digest);
void md5_transform(const u32 *w0, const u32 *w1, const u32 *w2, const u32 *w3, u32 *digest);

// Convenience function
void md5_hash(const u8 *input, int len, u8 *digest);

#endif // HASH_MD5_H