# Hash Benchmark Library - Implementation Guide

## Overview

This library extracts and centralizes hash functions from the hashcat project for benchmarking purposes. It provides a clean, standalone C implementation of popular hash algorithms without the complexity of the full hashcat framework.

## Current Implementation Status

### ✅ Completed
- **MD5**: Full implementation with test vectors
- **Build System**: Makefile with library creation and testing
- **Test Framework**: Correctness validation with known test vectors
- **Benchmark Framework**: Performance measurement tools
- **Core Infrastructure**: Type definitions, utility functions

### 🚧 In Progress
- **SHA1**: Header file created, implementation needed

### 📋 Planned (Top 30 Hash Functions from hashcat)

Based on hashcat module analysis, here are the most important hash functions to implement:

#### Tier 1 (Most Critical - Implement First)
1. **MD5** (module_00000) ✅ - DONE
2. **SHA1** (module_00100) 🚧 - Header ready
3. **SHA256** (module_01400) - Very common
4. **SHA512** (module_01700) - Very common
5. **NTLM** (module_01000) - Windows authentication
6. **MD4** (module_00900) - Legacy but still used

#### Tier 2 (High Priority)
7. **SHA224** (module_01300) - SHA-2 family
8. **SHA384** (module_10800) - SHA-2 family
9. **Blake2b** (module_00600) - Modern, fast
10. **Blake2s** (module_00610) - Modern, fast
11. **RIPEMD160** (module_06000) - Bitcoin/crypto
12. **Whirlpool** (module_06100) - ISO standard

#### Tier 3 (Medium Priority)
13. **bcrypt** (module_03200) - Password hashing
14. **scrypt** (module_08900) - Password hashing
15. **PBKDF2-HMAC-SHA1** (module_12000) - Key derivation
16. **PBKDF2-HMAC-SHA256** (module_10900) - Key derivation
17. **Argon2** (module_21600) - Modern password hashing
18. **CRC32** (module_11500) - Checksums
19. **Keccak-256** (module_17400) - SHA-3 family
20. **SHA3-256** (module_17400) - SHA-3 standard

#### Tier 4 (Lower Priority but Still Important)
21. **GOST R 34.11-94** (module_06900) - Russian standard
22. **Streebog-256** (module_11700) - Russian standard
23. **Streebog-512** (module_11800) - Russian standard
24. **SM3** (module_17300) - Chinese standard
25. **Tiger** (module_07000) - Fast hash
26. **HAVAL** (module_07100) - Variable output
27. **MD2** (module_08600) - Legacy
28. **PANAMA** (module_08700) - Stream cipher based
29. **FORK-256** (module_08800) - Research hash
30. **Snefru** (module_08900) - Historical

## Implementation Pattern

Each hash function follows this structure:

### 1. Header File (`include/hash_[name].h`)
```c
#ifndef HASH_[NAME]_H
#define HASH_[NAME]_H

#include "hash_types.h"

// Constants and macros
#define [NAME]_DIGEST_SIZE [size]
#define [NAME]_BLOCK_SIZE [size]

// Context structure
typedef struct {
    u32 h[N];        // Hash state
    u32 w0[4];       // Working buffer
    u32 w1[4];
    u32 w2[4];
    u32 w3[4];
    int len;         // Current length
} [name]_ctx_t;

// Function declarations
void [name]_init([name]_ctx_t *ctx);
void [name]_update([name]_ctx_t *ctx, const u8 *input, const int len);
void [name]_final([name]_ctx_t *ctx, u8 *digest);
void [name]_hash(const u8 *input, int len, u8 *digest);

#endif
```

### 2. Implementation File (`src/hash_[name].c`)
```c
#include "../include/hash_[name].h"
#include <string.h>

void [name]_transform(const u32 *w0, const u32 *w1, const u32 *w2, const u32 *w3, u32 *digest)
{
    // Core algorithm implementation
}

void [name]_init([name]_ctx_t *ctx)
{
    // Initialize hash state
}

void [name]_update([name]_ctx_t *ctx, const u8 *input, const int len)
{
    // Process input data
}

void [name]_final([name]_ctx_t *ctx, u8 *digest)
{
    // Finalize and output digest
}

void [name]_hash(const u8 *input, int len, u8 *digest)
{
    [name]_ctx_t ctx;
    [name]_init(&ctx);
    [name]_update(&ctx, input, len);
    [name]_final(&ctx, digest);
}
```

### 3. Test Vectors (`tests/test_hashes.c`)
Add test cases with known input/output pairs.

## Extracting from hashcat

To implement a new hash function from hashcat:

### Step 1: Identify the Module
- Find the module number in `src/modules/module_XXXXX.c`
- Check the `HASH_NAME` constant for the algorithm name

### Step 2: Locate Implementation Files
- Core algorithm: `OpenCL/inc_hash_[name].cl`
- Header definitions: `OpenCL/inc_hash_[name].h`
- Constants: Look for `#define` statements

### Step 3: Extract Constants
- Hash initial values (usually named `[NAME]C00`, `[NAME]C01`, etc.)
- Round constants
- Shift amounts
- Magic numbers

### Step 4: Adapt the Transform Function
- Copy the main transform function from the `.cl` file
- Replace OpenCL-specific macros with standard C equivalents:
  - `DECLSPEC` → remove
  - `PRIVATE_AS` → remove
  - `hc_rotl32_S` → use our utility function
  - `hc_add3_S` → use our utility function

### Step 5: Implement Context Management
- Create init, update, final functions following the pattern
- Handle padding and length encoding according to the algorithm spec

### Step 6: Add Tests
- Find test vectors in the module file (`ST_HASH` constant)
- Add to the test suite
- Verify correctness

## Building and Testing

```bash
# Build everything
make all

# Run tests
make test

# Run benchmarks
make benchmark

# Clean build
make clean

# Build specific hash
make md5
make sha1
```

## Performance Considerations

- All implementations are optimized for CPU execution
- Use compiler optimization flags (`-O3`)
- Consider SIMD instructions for bulk operations
- Profile critical paths for bottlenecks

## Adding New Hash Functions

1. Create header file in `include/`
2. Create implementation file in `src/`
3. Add test vectors to `tests/test_hashes.c`
4. Update Makefile if needed
5. Test correctness and performance

## License

This implementation is derived from hashcat (MIT License) and maintains the same license terms.