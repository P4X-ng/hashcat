# Standalone Hash Functions

This directory contains standalone hash function implementations extracted from hashcat for benchmarking and testing individual hash algorithms without running the full hashcat application.

## Overview

Hashcat contains implementations of many hash algorithms spread across multiple files. This standalone package extracts the core hash implementations (from `OpenCL/*.cl` and `OpenCL/*.h` files) for easy access and benchmarking.

## Available Hash Functions

The following hash functions are available in hashcat and can be extracted:

### **Top 30 Most Common Hash Algorithms:**

1. **MD4** - `inc_hash_md4`
2. **MD5** - `inc_hash_md5`
3. **SHA1** - `inc_hash_sha1`
4. **SHA224** - `inc_hash_sha224`
5. **SHA256** - `inc_hash_sha256`
6. **SHA384** - `inc_hash_sha384`
7. **SHA512** - `inc_hash_sha512`
8. **RIPEMD160** - `inc_hash_ripemd160`
9. **RIPEMD320** - `inc_hash_ripemd320`
10. **Whirlpool** - `inc_hash_whirlpool`
11. **BLAKE2b** - `inc_hash_blake2b`
12. **BLAKE2s** - `inc_hash_blake2s`
13. **GOST R 34.11-94** - `inc_hash_gost94`
14. **SM3** - `inc_hash_sm3`
15. **Streebog256** - `inc_hash_streebog256`
16. **Streebog512** - `inc_hash_streebog512`
17. **MD6** - `inc_hash_md6`
18. **Argon2** - `inc_hash_argon2`
19. **scrypt** - `inc_hash_scrypt`
20. **Base58** (Bitcoin) - `inc_hash_base58`

## Directory Structure

```
standalone_hashes/
├── README.md              # This file
├── extract_hashes.sh      # Script to copy hash files from OpenCL directory
├── list_hashes.sh         # List available hash functions
├── hashes/                # Extracted hash function files (created by extract_hashes.sh)
│   ├── inc_hash_md5.h
│   ├── inc_hash_md5.cl
│   ├── inc_hash_sha256.h
│   ├── inc_hash_sha256.cl
│   └── ... (other hash files)
└── benchmark_example.txt  # Example of how to use these files

```

## Quick Start

### Option 1: Benchmark Using Hashcat (Recommended)

The easiest way to benchmark individual hash functions is to use hashcat's built-in benchmark mode:

```bash
# Show available hash functions for benchmarking
./benchmark_hashes.sh

# Benchmark specific hash functions
./benchmark_hashes.sh MD5 SHA256 SHA512

# Benchmark all available hash functions
./benchmark_hashes.sh all
```

### Option 2: Extract Hash Functions for Custom Use

If you want to extract the raw hash implementations for your own projects:

1. **Extract Hash Functions**

```bash
./extract_hashes.sh
```

This copies all `inc_hash_*.h` and `inc_hash_*.cl` files from the `OpenCL` directory into the `hashes/` subdirectory.

2. **List Available Hash Functions**

```bash
./list_hashes.sh
```

3. **Use in Your Own Code (Advanced)**

The hash function files are self-contained implementations that you can integrate into your own projects:

```c
// Example: Using MD5 hash function
#include "hashes/inc_hash_md5.h"
#include "hashes/inc_hash_md5.cl"

// Initialize, update, and finalize the hash
md5_ctx_t ctx;
md5_init(&ctx);
md5_update(&ctx, data, len);
md5_final(&ctx);

// ctx.h now contains the hash digest
```

## Benchmarking

To benchmark a specific hash algorithm:

1. Extract the relevant hash files
2. Write a simple C program that repeatedly calls the hash functions
3. Use `time` or performance profiling tools
4. Compare performance across different algorithms

Example benchmarking pseudocode:

```c
for (i = 0; i < 10000000; i++) {
    md5_init(&ctx);
    md5_update(&ctx, test_data, test_len);
    md5_final(&ctx);
}
```

## Integration with Other Projects

These hash functions are written to work with hashcat's OpenCL kernels. To use them in standard C code, you may need to:

1. Define the required types (`u32`, `u64`, etc.) - see `OpenCL/inc_types.h`
2. Implement helper functions (rotation, swap, etc.) - see `OpenCL/inc_platform.cl`
3. Define address space qualifiers (`PRIVATE_AS`, `GLOBAL_AS`) as empty macros for CPU code

## File Organization

Each hash algorithm typically has two files:

- **`.h` file**: Contains type definitions, macros, constants, and function declarations
- **`.cl` file**: Contains the actual implementation of the hash functions

## Notes

- These implementations are optimized for GPUs/OpenCL and may need adaptation for CPU-only use
- The files have dependencies on hashcat's common infrastructure files
- For production use, consider using established crypto libraries (OpenSSL, libsodium, etc.)
- These are extracted for educational, testing, and benchmarking purposes

## Building

For a simple standalone build, you'll need to:

1. Extract the hash files
2. Create wrapper code that defines the necessary types and macros
3. Compile with: `gcc -O3 -march=native your_code.c -o benchmark`

## License

These hash implementations are part of hashcat and are licensed under the MIT license.  
See `docs/credits.txt` in the main hashcat directory for full credits and license information.

## Support

For questions about the hash implementations, refer to:
- [Hashcat Website](https://hashcat.net/)
- [Hashcat GitHub](https://github.com/hashcat/hashcat)
- [Hashcat Forums](https://hashcat.net/forum/)
- [Hashcat Wiki](https://hashcat.net/wiki/)
