/**
 * Hash Benchmark Library - Performance Benchmark
 * License: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "hash_md5.h"

#define BENCHMARK_ITERATIONS 1000000
#define BENCHMARK_DATA_SIZE 1024

double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

void benchmark_md5()
{
    printf("Benchmarking MD5...\n");
    
    // Prepare test data
    u8 *data = malloc(BENCHMARK_DATA_SIZE);
    u8 digest[16];
    
    for (int i = 0; i < BENCHMARK_DATA_SIZE; i++) {
        data[i] = (u8)(i & 0xFF);
    }
    
    // Warm up
    for (int i = 0; i < 1000; i++) {
        md5_hash(data, BENCHMARK_DATA_SIZE, digest);
    }
    
    // Benchmark
    double start_time = get_time();
    
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        md5_hash(data, BENCHMARK_DATA_SIZE, digest);
    }
    
    double end_time = get_time();
    double elapsed = end_time - start_time;
    
    double bytes_per_second = (double)(BENCHMARK_ITERATIONS * BENCHMARK_DATA_SIZE) / elapsed;
    double mb_per_second = bytes_per_second / (1024 * 1024);
    double hashes_per_second = BENCHMARK_ITERATIONS / elapsed;
    
    printf("  Iterations: %d\n", BENCHMARK_ITERATIONS);
    printf("  Data size: %d bytes\n", BENCHMARK_DATA_SIZE);
    printf("  Time: %.3f seconds\n", elapsed);
    printf("  Throughput: %.2f MB/s\n", mb_per_second);
    printf("  Hash rate: %.0f hashes/second\n", hashes_per_second);
    printf("  Final digest: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n\n");
    
    free(data);
}

void benchmark_small_inputs()
{
    printf("Benchmarking MD5 with small inputs...\n");
    
    const char *test_string = "hashcat";
    u8 digest[16];
    
    // Warm up
    for (int i = 0; i < 1000; i++) {
        md5_hash((const u8*)test_string, strlen(test_string), digest);
    }
    
    // Benchmark
    double start_time = get_time();
    
    for (int i = 0; i < BENCHMARK_ITERATIONS * 10; i++) {
        md5_hash((const u8*)test_string, strlen(test_string), digest);
    }
    
    double end_time = get_time();
    double elapsed = end_time - start_time;
    
    double hashes_per_second = (BENCHMARK_ITERATIONS * 10) / elapsed;
    
    printf("  Input: \"%s\" (%zu bytes)\n", test_string, strlen(test_string));
    printf("  Iterations: %d\n", BENCHMARK_ITERATIONS * 10);
    printf("  Time: %.3f seconds\n", elapsed);
    printf("  Hash rate: %.0f hashes/second\n", hashes_per_second);
    printf("  Final digest: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n\n");
}

int main()
{
    printf("Hash Benchmark Library Performance Test\n");
    printf("=======================================\n\n");
    
    benchmark_md5();
    benchmark_small_inputs();
    
    printf("Benchmark complete!\n");
    return 0;
}