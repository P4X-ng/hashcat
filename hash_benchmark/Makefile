# Hash Benchmark Library Makefile
# Extracted and adapted from hashcat
# License: MIT

CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 -Iinclude
LDFLAGS = 

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
TESTDIR = tests

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Library name
LIBRARY = libhash_benchmark.a

# Test programs
TEST_SOURCES = $(wildcard $(TESTDIR)/*.c)
TEST_PROGRAMS = $(TEST_SOURCES:$(TESTDIR)/%.c=$(BUILDDIR)/%)

# Default target
all: $(BUILDDIR)/$(LIBRARY) $(TEST_PROGRAMS)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Compile object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library
$(BUILDDIR)/$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

# Compile test programs
$(BUILDDIR)/%: $(TESTDIR)/%.c $(BUILDDIR)/$(LIBRARY) | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -L$(BUILDDIR) -lhash_benchmark -o $@

# Individual hash algorithms
md5: $(BUILDDIR)/hash_md5.o
sha1: $(BUILDDIR)/hash_sha1.o

# Test target
test: $(BUILDDIR)/test_hashes
	./$(BUILDDIR)/test_hashes

# Benchmark target
benchmark: $(BUILDDIR)/benchmark
	./$(BUILDDIR)/benchmark

# Clean target
clean:
	rm -rf $(BUILDDIR)

# Install target
install: $(BUILDDIR)/$(LIBRARY)
	cp $(BUILDDIR)/$(LIBRARY) /usr/local/lib/
	cp $(INCDIR)/*.h /usr/local/include/

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build library and tests"
	@echo "  test      - Run test suite"
	@echo "  benchmark - Run benchmarks"
	@echo "  clean     - Remove build files"
	@echo "  install   - Install library system-wide"
	@echo "  md5       - Build MD5 only"
	@echo "  sha1      - Build SHA1 only"

.PHONY: all test benchmark clean install help md5 sha1