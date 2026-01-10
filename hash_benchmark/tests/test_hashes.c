/**
 * Hash Benchmark Library - Test Suite
 * License: MIT
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hash_md5.h"

// Test vectors for MD5
typedef struct {
    const char *input;
    const char *expected_md5;
} test_vector_t;

static test_vector_t test_vectors[] = {
    {"", "d41d8cd98f00b204e9800998ecf8427e"},
    {"a", "0cc175b9c0f1b6a831c399e269772661"},
    {"abc", "900150983cd24fb0d6963f7d28e17f72"},
    {"hashcat", "8743b52063cd84097a65d1633f5c74f5"},
    {NULL, NULL}
};

void print_hex(const u8 *data, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
}

int hex_to_bytes(const char *hex, u8 *bytes, int max_len)
{
    int len = strlen(hex) / 2;
    if (len > max_len) return -1;
    
    for (int i = 0; i < len; i++) {
        sscanf(hex + 2*i, "%2hhx", &bytes[i]);
    }
    return len;
}

int test_md5()
{
    printf("Testing MD5...\n");
    int passed = 0;
    int total = 0;
    
    for (int i = 0; test_vectors[i].input != NULL; i++) {
        total++;
        
        u8 digest[16];
        u8 expected[16];
        
        // Compute hash
        md5_hash((const u8*)test_vectors[i].input, strlen(test_vectors[i].input), digest);
        
        // Convert expected result
        hex_to_bytes(test_vectors[i].expected_md5, expected, 16);
        
        // Compare
        if (memcmp(digest, expected, 16) == 0) {
            printf("  Test %d: PASS - \"%s\"\n", i + 1, test_vectors[i].input);
            passed++;
        } else {
            printf("  Test %d: FAIL - \"%s\"\n", i + 1, test_vectors[i].input);
            printf("    Expected: %s\n", test_vectors[i].expected_md5);
            printf("    Got:      ");
            print_hex(digest, 16);
            printf("\n");
        }
    }
    
    printf("MD5 Tests: %d/%d passed\n\n", passed, total);
    return passed == total;
}

int main()
{
    printf("Hash Benchmark Library Test Suite\n");
    printf("==================================\n\n");
    
    int all_passed = 1;
    
    all_passed &= test_md5();
    
    if (all_passed) {
        printf("All tests passed!\n");
        return 0;
    } else {
        printf("Some tests failed!\n");
        return 1;
    }
}