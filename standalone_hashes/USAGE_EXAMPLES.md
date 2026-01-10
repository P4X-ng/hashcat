# Usage Examples

This document provides practical examples for using the standalone hash functions extracted from hashcat.

## Example 1: List All Available Hash Functions

```bash
cd standalone_hashes
./list_hashes.sh
```

Output:
```
========================================
Available Hash Functions in Hashcat
========================================

Hash Algorithm              Header File                Implementation File
--------------------------------------------------------------------------------
ARGON2                   inc_hash_argon2.h    inc_hash_argon2.cl
BASE58                   inc_hash_base58.h    inc_hash_base58.cl
BLAKE2B                  inc_hash_blake2b.h    inc_hash_blake2b.cl
BLAKE2S                  inc_hash_blake2s.h    inc_hash_blake2s.cl
MD4                      inc_hash_md4.h    inc_hash_md4.cl
MD5                      inc_hash_md5.h    inc_hash_md5.cl
SHA1                     inc_hash_sha1.h    inc_hash_sha1.cl
SHA256                   inc_hash_sha256.h    inc_hash_sha256.cl
SHA512                   inc_hash_sha512.h    inc_hash_sha512.cl
... (and more)
```

## Example 2: Extract Hash Functions

```bash
cd standalone_hashes
./extract_hashes.sh
```

This creates a `hashes/` directory containing all 40 extracted files (20 `.h` and 20 `.cl` files).

## Example 3: Benchmark Specific Hash Functions

### Using the benchmark script (easiest method):

```bash
cd standalone_hashes

# Show available hash functions for benchmarking
./benchmark_hashes.sh

# Benchmark MD5
./benchmark_hashes.sh MD5

# Benchmark multiple hashes
./benchmark_hashes.sh MD5 SHA256 SHA512

# Benchmark all available hashes
./benchmark_hashes.sh all
```

### Using hashcat directly:

```bash
cd /path/to/hashcat

# Benchmark MD5 (mode 0)
./hashcat -b -m 0

# Benchmark SHA256 (mode 1400)
./hashcat -b -m 1400

# Benchmark SHA512 (mode 1700)
./hashcat -b -m 1700
```

## Example 4: Examine Hash Implementation

```bash
cd standalone_hashes/hashes

# View MD5 header to see data structures and constants
less inc_hash_md5.h

# View MD5 implementation to see the algorithm
less inc_hash_md5.cl

# Search for specific function in SHA256 implementation
grep -n "sha256_init" inc_hash_sha256.cl
```

## Example 5: Compare Hash Algorithms

Create a simple comparison script:

```bash
#!/bin/bash
# compare_hashes.sh

cd standalone_hashes

echo "Comparing hash function performance..."
echo "======================================"

for hash in MD5 SHA1 SHA256 SHA512; do
  echo ""
  echo "Testing $hash..."
  ./benchmark_hashes.sh $hash
done
```

## Example 6: Using with Makefile

```bash
cd standalone_hashes

# Show available make targets
make help

# Extract hash functions
make extract

# List hash functions
make list

# Clean extracted files
make clean
```

## Example 7: Inspect Specific Hash Algorithm

Let's say you want to understand how SHA256 works:

```bash
cd standalone_hashes

# Extract the files first
./extract_hashes.sh

# Examine the SHA256 header
cat hashes/inc_hash_sha256.h

# Look for the init function
grep -A 20 "sha256_init" hashes/inc_hash_sha256.cl

# Look for the transform function
grep -A 50 "sha256_transform" hashes/inc_hash_sha256.cl
```

## Example 8: Create a Simple Test Program (Advanced)

While the extracted files are OpenCL implementations and require significant infrastructure to run directly, you can study them to understand the algorithms. For actual CPU implementation, consider:

```c
// Using OpenSSL library (much easier for CPU benchmarking)
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void benchmark_md5() {
    const char *data = "hello world";
    unsigned char digest[MD5_DIGEST_LENGTH];
    
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++) {
        MD5((unsigned char*)data, strlen(data), digest);
    }
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MD5: %.2f seconds for 1M hashes\n", time_spent);
    printf("Rate: %.0f hashes/sec\n", 1000000.0 / time_spent);
}

int main() {
    benchmark_md5();
    return 0;
}
```

Compile and run:
```bash
gcc -O3 benchmark.c -o benchmark -lcrypto
./benchmark
```

## Example 9: Hash Mode Reference

Common hash modes for benchmarking with hashcat:

| Hash Algorithm | Mode | Command |
|----------------|------|---------|
| MD4            | 900  | `./benchmark_hashes.sh MD4` |
| MD5            | 0    | `./benchmark_hashes.sh MD5` |
| SHA1           | 100  | `./benchmark_hashes.sh SHA1` |
| SHA224         | 1300 | `./benchmark_hashes.sh SHA224` |
| SHA256         | 1400 | `./benchmark_hashes.sh SHA256` |
| SHA384         | 10800| `./benchmark_hashes.sh SHA384` |
| SHA512         | 1700 | `./benchmark_hashes.sh SHA512` |
| RIPEMD160      | 6000 | `./benchmark_hashes.sh RIPEMD160` |
| Whirlpool      | 6100 | `./benchmark_hashes.sh Whirlpool` |
| BLAKE2b-512    | 600  | `./benchmark_hashes.sh BLAKE2b-512` |

## Example 10: Examining File Sizes

```bash
cd standalone_hashes/hashes

# Show file sizes
ls -lh inc_hash_*.cl | awk '{print $9, $5}'

# Count lines of code in each implementation
wc -l inc_hash_*.cl | sort -n

# Find the largest implementation
ls -lS inc_hash_*.cl | head -5
```

## Tips

1. **Performance**: The extracted OpenCL files are optimized for GPU execution. For CPU benchmarking, use established libraries like OpenSSL or libsodium.

2. **Learning**: These files are excellent for understanding cryptographic hash implementations, but they require OpenCL infrastructure to run directly.

3. **Integration**: For production use in your own projects, consider using well-tested crypto libraries rather than extracting these implementations.

4. **Benchmarking**: The easiest way to benchmark is using hashcat's built-in benchmark mode with the `benchmark_hashes.sh` script.

5. **Documentation**: Refer to the [Hashcat Wiki](https://hashcat.net/wiki/) for more information about hash modes and algorithms.
