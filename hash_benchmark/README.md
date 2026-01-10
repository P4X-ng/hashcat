# Hash Benchmark Library

**Centralized hash functions extracted from hashcat for benchmarking and testing**

This library extracts the most important hash algorithms from the hashcat project and provides them as a clean, standalone C library suitable for benchmarking, testing, and educational purposes.

## 🚀 Quick Start

```bash
# Clone or extract to your system
cd hash_benchmark

# Build everything
make all

# Run tests to verify correctness
make test

# Run performance benchmarks
./benchmark.sh
```

## 📋 What's Included

### ✅ Currently Implemented
- **MD5** - Complete implementation with test vectors
- **Build System** - Makefile with library creation and testing
- **Test Framework** - Correctness validation
- **Benchmark Suite** - Performance measurement tools

### 🎯 Ready to Implement (Top 30 from hashcat)
The library is designed to easily add the most important hash functions:

**Tier 1 (Critical)**: SHA1, SHA256, SHA512, NTLM, MD4  
**Tier 2 (High Priority)**: Blake2b/s, SHA224/384, RIPEMD160, Whirlpool  
**Tier 3 (Password Hashing)**: bcrypt, scrypt, Argon2, PBKDF2 variants  
**Tier 4 (Specialized)**: CRC32, Keccak, SHA3, GOST, Streebog, SM3  

See [HASH_FUNCTIONS.md](HASH_FUNCTIONS.md) for the complete list.

## 🔧 Usage

### Simple Hashing
```c
#include "hash_md5.h"

u8 digest[16];
const char *input = "hello world";
md5_hash((const u8*)input, strlen(input), digest);

// Print hex result
for (int i = 0; i < 16; i++) {
    printf("%02x", digest[i]);
}
```

### Streaming Interface
```c
#include "hash_md5.h"

md5_ctx_t ctx;
md5_init(&ctx);

// Process data in chunks
md5_update(&ctx, chunk1, len1);
md5_update(&ctx, chunk2, len2);

// Get final result
u8 digest[16];
md5_final(&ctx, digest);
```

## 🏗️ Build System

```bash
# Build everything
make all

# Build just the library
make build/libhash_benchmark.a

# Build specific hash function
make md5

# Run correctness tests
make test

# Run performance benchmarks
make benchmark

# Clean build files
make clean

# Install system-wide
sudo make install
```

## 📊 Benchmarking

The included benchmark suite tests:
- **Throughput**: MB/s for large data processing
- **Latency**: Hashes/second for small inputs
- **Correctness**: Validation against known test vectors

```bash
# Automated benchmark script
./benchmark.sh

# Manual benchmark
make benchmark
./build/benchmark
```

Example output:
```
Benchmarking MD5...
  Iterations: 1000000
  Data size: 1024 bytes
  Time: 0.234 seconds
  Throughput: 4172.65 MB/s
  Hash rate: 4273504 hashes/second
```

## 🧪 Testing

Comprehensive test suite with known test vectors:

```bash
# Run all tests
make test

# Expected output:
# Testing MD5...
#   Test 1: PASS - ""
#   Test 2: PASS - "a"
#   Test 3: PASS - "abc"
#   Test 4: PASS - "hashcat"
# MD5 Tests: 4/4 passed
# 
# All tests passed!
```

## 📁 Project Structure

```
hash_benchmark/
├── README.md                 # This file
├── IMPLEMENTATION_GUIDE.md   # How to add new hash functions
├── HASH_FUNCTIONS.md         # Complete hash function reference
├── Makefile                  # Build system
├── benchmark.sh              # Automated benchmark script
├── include/                  # Header files
│   ├── hash_types.h         # Common types and utilities
│   ├── hash_md5.h           # MD5 interface
│   └── hash_sha1.h          # SHA1 interface (header only)
├── src/                      # Implementation files
│   └── hash_md5.c           # MD5 implementation
├── tests/                    # Test and benchmark programs
│   ├── test_hashes.c        # Correctness tests
│   └── benchmark.c          # Performance benchmarks
└── build/                    # Build artifacts (created by make)
    ├── libhash_benchmark.a  # Static library
    ├── test_hashes          # Test executable
    └── benchmark            # Benchmark executable
```

## 🔍 Implementation Details

### Extracted from hashcat
- **Source**: hashcat OpenCL implementations (`OpenCL/inc_hash_*.cl`)
- **Adapted**: Converted from GPU to CPU code
- **Verified**: Test vectors from hashcat modules
- **Optimized**: Compiler optimizations for CPU performance

### Design Principles
- **Clean API**: Simple, consistent function interfaces
- **No Dependencies**: Standalone C99 code
- **High Performance**: Optimized for CPU execution
- **Correct Implementation**: Verified against reference implementations
- **Easy Extension**: Pattern for adding new algorithms

## 📈 Performance Notes

- Compiled with `-O3` optimization
- Uses efficient bit manipulation and rotation
- CPU-optimized (no GPU dependencies)
- Suitable for both throughput and latency testing
- Memory-efficient implementations

## 🤝 Contributing

### Adding New Hash Functions

1. **Find the hashcat module**: `src/modules/module_XXXXX.c`
2. **Extract OpenCL code**: `OpenCL/inc_hash_[name].cl`
3. **Follow the pattern**: See [IMPLEMENTATION_GUIDE.md](IMPLEMENTATION_GUIDE.md)
4. **Add tests**: Include test vectors
5. **Benchmark**: Verify performance

### Priority List
The most valuable additions would be:
1. **SHA1** (header exists, needs implementation)
2. **SHA256** (very commonly used)
3. **SHA512** (high security applications)
4. **Blake2b** (modern, fast alternative)

## 📄 License

MIT License - Same as hashcat source code

This library is derived from hashcat and maintains compatibility with its MIT license terms.

## 🔗 References

- [hashcat project](https://github.com/hashcat/hashcat)
- [Original OpenCL implementations](https://github.com/hashcat/hashcat/tree/master/OpenCL)
- Algorithm specifications and RFCs
- NIST cryptographic standards

## ⚡ Why This Library?

- **Focused**: Just the hash functions, no password cracking
- **Portable**: Standard C99, no GPU dependencies  
- **Fast**: Optimized for CPU benchmarking
- **Clean**: Simple API, easy to integrate
- **Verified**: Test vectors ensure correctness
- **Extensible**: Easy to add more algorithms

Perfect for:
- Performance benchmarking
- Algorithm comparison
- Educational purposes
- Integration into other projects
- Cryptographic research