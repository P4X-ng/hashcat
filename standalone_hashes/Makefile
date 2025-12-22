##
## Makefile for Standalone Hash Benchmarking
## Author......: See docs/credits.txt
## License.....: MIT
##

# This is a template Makefile for creating standalone benchmarks
# The hash functions are extracted but require OpenCL infrastructure
# For CPU-only benchmarking, consider using standard crypto libraries

.PHONY: help extract list clean

help:
	@echo "=================================================="
	@echo "Hashcat Standalone Hash Functions - Makefile"
	@echo "=================================================="
	@echo ""
	@echo "Available targets:"
	@echo "  make extract    - Extract hash functions from OpenCL directory"
	@echo "  make list       - List all available hash functions"
	@echo "  make clean      - Remove extracted files"
	@echo "  make help       - Show this help message"
	@echo ""
	@echo "Note: The extracted hash functions are OpenCL implementations"
	@echo "      and require GPU infrastructure to run."
	@echo ""
	@echo "For CPU benchmarking, consider using:"
	@echo "  - OpenSSL library (libssl-dev)"
	@echo "  - libsodium"
	@echo "  - Crypto++"
	@echo ""

extract:
	@echo "Extracting hash functions..."
	@./extract_hashes.sh

list:
	@./list_hashes.sh

clean:
	@echo "Cleaning extracted files..."
	@rm -rf hashes/
	@echo "Done!"
