# Hash Functions Reference

## Extracted from hashcat - Top Hash Algorithms

This document lists the hash functions extracted from hashcat, organized by priority and implementation status.

## Implementation Status

### ✅ Fully Implemented
- **MD5** - Message Digest 5 (RFC 1321)
  - Module: `module_00000.c`
  - Digest Size: 128 bits (16 bytes)
  - Block Size: 512 bits (64 bytes)
  - Usage: `md5_hash(input, len, digest)`

### 🚧 Headers Ready (Need Implementation)
- **SHA1** - Secure Hash Algorithm 1 (RFC 3174)
  - Module: `module_00100.c`
  - Digest Size: 160 bits (20 bytes)
  - Block Size: 512 bits (64 bytes)

## Priority Implementation List

### Tier 1: Essential Cryptographic Hashes
| Algorithm | Module | Digest Size | Status | Priority |
|-----------|--------|-------------|--------|----------|
| MD5 | 00000 | 128 bit | ✅ Done | Critical |
| SHA1 | 00100 | 160 bit | 🚧 Header | Critical |
| SHA256 | 01400 | 256 bit | ❌ Todo | Critical |
| SHA512 | 01700 | 512 bit | ❌ Todo | Critical |
| NTLM | 01000 | 128 bit | ❌ Todo | High |
| MD4 | 00900 | 128 bit | ❌ Todo | High |

### Tier 2: Modern and Secure Hashes
| Algorithm | Module | Digest Size | Status | Priority |
|-----------|--------|-------------|--------|----------|
| SHA224 | 01300 | 224 bit | ❌ Todo | High |
| SHA384 | 10800 | 384 bit | ❌ Todo | High |
| Blake2b | 00600 | Variable | ❌ Todo | High |
| Blake2s | 00610 | Variable | ❌ Todo | High |
| RIPEMD160 | 06000 | 160 bit | ❌ Todo | Medium |
| Whirlpool | 06100 | 512 bit | ❌ Todo | Medium |

### Tier 3: Password Hashing Functions
| Algorithm | Module | Type | Status | Priority |
|-----------|--------|------|--------|----------|
| bcrypt | 03200 | Adaptive | ❌ Todo | High |
| scrypt | 08900 | Memory-hard | ❌ Todo | High |
| Argon2 | 21600 | Memory-hard | ❌ Todo | High |
| PBKDF2-SHA1 | 12000 | Key derivation | ❌ Todo | Medium |
| PBKDF2-SHA256 | 10900 | Key derivation | ❌ Todo | Medium |

### Tier 4: Specialized and Legacy Hashes
| Algorithm | Module | Digest Size | Status | Use Case |
|-----------|--------|-------------|--------|----------|
| CRC32 | 11500 | 32 bit | ❌ Todo | Checksums |
| Keccak-256 | 17400 | 256 bit | ❌ Todo | Ethereum |
| SHA3-256 | 17400 | 256 bit | ❌ Todo | Modern |
| GOST R 34.11-94 | 06900 | 256 bit | ❌ Todo | Russian std |
| Streebog-256 | 11700 | 256 bit | ❌ Todo | Russian std |
| Streebog-512 | 11800 | 512 bit | ❌ Todo | Russian std |
| SM3 | 17300 | 256 bit | ❌ Todo | Chinese std |

## Usage Examples

### MD5 (Currently Available)
```c
#include "hash_md5.h"

// Simple hash
u8 digest[16];
const char *input = "hello world";
md5_hash((const u8*)input, strlen(input), digest);

// Streaming hash
md5_ctx_t ctx;
md5_init(&ctx);
md5_update(&ctx, (const u8*)input, strlen(input));
md5_final(&ctx, digest);

// Print result
for (int i = 0; i < 16; i++) {
    printf("%02x", digest[i]);
}
```

### SHA1 (Header Available, Implementation Needed)
```c
#include "hash_sha1.h"

// Will be available after implementation
u8 digest[20];
sha1_hash((const u8*)input, strlen(input), digest);
```

## Performance Characteristics

Based on typical CPU implementations:

| Algorithm | Speed Rank | Security | Use Case |
|-----------|------------|----------|----------|
| MD5 | Fastest | Broken | Legacy/checksums |
| SHA1 | Fast | Deprecated | Legacy |
| SHA256 | Medium | Secure | General purpose |
| SHA512 | Medium | Secure | High security |
| Blake2b | Very Fast | Secure | Modern choice |
| Blake2s | Very Fast | Secure | 32-bit systems |
| bcrypt | Slow (by design) | Secure | Passwords |
| scrypt | Slow (by design) | Secure | Passwords |
| Argon2 | Slow (by design) | Secure | Passwords |

## Implementation Notes

### From hashcat OpenCL to C
- Removed GPU-specific optimizations
- Converted vector operations to scalar
- Maintained algorithmic correctness
- Added proper padding and finalization

### Test Vectors
Each implementation includes test vectors from:
- RFC specifications
- hashcat's built-in test cases (`ST_HASH` constants)
- NIST test vectors where available

### Build System
```bash
# Build all implemented functions
make all

# Test correctness
make test

# Benchmark performance
make benchmark

# Build specific algorithm
make md5
```

## Contributing

To add a new hash function:

1. **Extract from hashcat**:
   - Find module in `src/modules/module_XXXXX.c`
   - Locate OpenCL implementation in `OpenCL/inc_hash_[name].cl`
   - Get constants from `OpenCL/inc_hash_[name].h`

2. **Implement**:
   - Create header file following the pattern
   - Implement core transform function
   - Add init/update/final functions
   - Create convenience hash function

3. **Test**:
   - Add test vectors to test suite
   - Verify against known good implementations
   - Add to benchmark suite

4. **Document**:
   - Update this reference
   - Add usage examples
   - Note any special considerations

## References

- [hashcat source code](https://github.com/hashcat/hashcat)
- RFC specifications for each algorithm
- NIST cryptographic standards
- Algorithm-specific documentation