#!/bin/bash

# Hash Benchmark Library - Automated Benchmark Script
# License: MIT

set -e

echo "Hash Benchmark Library - Automated Build and Test"
echo "================================================="
echo

# Clean previous builds
echo "Cleaning previous builds..."
make clean
echo

# Build the library
echo "Building hash library..."
make all
echo

# Run tests
echo "Running correctness tests..."
make test
echo

# Run benchmarks
echo "Running performance benchmarks..."
make benchmark
echo

# Show library info
echo "Library information:"
echo "==================="
if [ -f "build/libhash_benchmark.a" ]; then
    echo "Library size: $(du -h build/libhash_benchmark.a | cut -f1)"
    echo "Library contents:"
    ar -t build/libhash_benchmark.a | sed 's/^/  /'
else
    echo "Library not found!"
fi
echo

# Show available hash functions
echo "Available hash functions:"
echo "========================"
echo "- MD5 (implemented)"
echo "- SHA1 (header only)"
echo "- More to be added..."
echo

echo "Benchmark complete! Check the results above."
echo "To add more hash functions, implement them in src/ and include/"