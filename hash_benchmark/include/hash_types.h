/**
 * Hash Benchmark Library - Core Types
 * Extracted and adapted from hashcat
 * License: MIT
 */

#ifndef HASH_TYPES_H
#define HASH_TYPES_H

#include <stdint.h>
#include <string.h>

// Basic type definitions
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Aligned types
typedef u8  u8a;
typedef u16 u16a;
typedef u32 u32a;
typedef u64 u64a;

// Common constants
#define MAYBE_UNUSED __attribute__((unused))

// Rotation macros
#define ROTL32(a,n) (((a) << (n)) | ((a) >> (32 - (n))))
#define ROTR32(a,n) (((a) >> (n)) | ((a) << (32 - (n))))
#define ROTL64(a,n) (((a) << (n)) | ((a) >> (64 - (n))))
#define ROTR64(a,n) (((a) >> (n)) | ((a) << (64 - (n))))

// Utility functions
static inline u32 hc_rotl32_S(const u32 a, const int n)
{
  return ROTL32(a, n);
}

static inline u32 hc_rotr32_S(const u32 a, const int n)
{
  return ROTR32(a, n);
}

static inline u64 hc_rotl64_S(const u64 a, const int n)
{
  return ROTL64(a, n);
}

static inline u64 hc_rotr64_S(const u64 a, const int n)
{
  return ROTR64(a, n);
}

static inline u32 hc_add3_S(const u32 a, const u32 b, const u32 c)
{
  return a + b + c;
}

static inline u32 hc_bytealign_S(const u32 a, const u32 b, const int c)
{
  return (a << ((4 - c) * 8)) | (b >> (c * 8));
}

// Endianness conversion
static inline u32 hc_swap32_S(const u32 v)
{
  return ((v & 0x000000ff) << 24)
       | ((v & 0x0000ff00) <<  8)
       | ((v & 0x00ff0000) >>  8)
       | ((v & 0xff000000) >> 24);
}

static inline u64 hc_swap64_S(const u64 v)
{
  return ((v & 0x00000000000000ffULL) << 56)
       | ((v & 0x000000000000ff00ULL) << 40)
       | ((v & 0x0000000000ff0000ULL) << 24)
       | ((v & 0x00000000ff000000ULL) <<  8)
       | ((v & 0x000000ff00000000ULL) >>  8)
       | ((v & 0x0000ff0000000000ULL) >> 24)
       | ((v & 0x00ff000000000000ULL) >> 40)
       | ((v & 0xff00000000000000ULL) >> 56);
}

// Hash result structure
typedef struct {
  u32 digest[16];  // Large enough for any hash
  int digest_size; // Size in 32-bit words
} hash_result_t;

// Hash context base structure
typedef struct {
  u32 h[16];       // Hash state (large enough for any algorithm)
  u8  buffer[256]; // Input buffer (large enough for any block size)
  u64 total_len;   // Total length processed
  int buffer_len;  // Current buffer length
  int block_size;  // Algorithm block size
  int digest_size; // Algorithm digest size
} hash_ctx_t;

#endif // HASH_TYPES_H