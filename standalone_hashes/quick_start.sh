#!/usr/bin/env bash
##
## Quick Start Script
## Demonstrates the standalone hash extraction utility
##

set -e

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}======================================================${NC}"
echo -e "${BLUE}Hashcat Standalone Hash Functions - Quick Start${NC}"
echo -e "${BLUE}======================================================${NC}"
echo ""

# Step 1: List available hashes
echo -e "${GREEN}Step 1: Listing available hash functions...${NC}"
echo ""
./list_hashes.sh
echo ""
read -p "Press Enter to continue..."
echo ""

# Step 2: Extract hash functions
echo -e "${GREEN}Step 2: Extracting hash functions...${NC}"
echo ""
if [ -d "hashes" ]; then
  echo -e "${YELLOW}Hashes directory already exists. Skipping extraction.${NC}"
else
  ./extract_hashes.sh
fi
echo ""
read -p "Press Enter to continue..."
echo ""

# Step 3: Show what was extracted
echo -e "${GREEN}Step 3: Showing extracted files...${NC}"
echo ""
if [ -d "hashes" ] && [ -n "$(ls -A hashes 2>/dev/null)" ]; then
  echo "Header files (.h):"
  find hashes -name "*.h" -type f | wc -l
  echo ""
  echo "Implementation files (.cl):"
  find hashes -name "*.cl" -type f | wc -l
  echo ""
  echo "Sample files:"
  find hashes -name "*.h" -type f | head -5
else
  echo -e "${YELLOW}No files found in hashes directory.${NC}"
fi
echo ""
read -p "Press Enter to continue..."
echo ""

# Step 4: Examine a hash function
echo -e "${GREEN}Step 4: Examining MD5 hash function...${NC}"
echo ""
if [ -f "hashes/inc_hash_md5.h" ]; then
  echo "MD5 header file (first 30 lines):"
  head -30 hashes/inc_hash_md5.h
else
  echo -e "${YELLOW}MD5 header file not found. Please run extraction first.${NC}"
fi
echo ""
read -p "Press Enter to continue..."
echo ""

# Step 5: Show benchmarking options
echo -e "${GREEN}Step 5: Benchmarking options...${NC}"
echo ""
echo "To benchmark hash functions, you can:"
echo "  1. Use the benchmark script: ./benchmark_hashes.sh MD5 SHA256 SHA512"
echo "  2. Use hashcat directly: ./hashcat -b -m 0 (for MD5)"
echo "  3. Compare multiple hashes: ./benchmark_hashes.sh all"
echo ""
echo "Note: Benchmarking requires hashcat to be built."
echo ""

# Final message
echo -e "${BLUE}======================================================${NC}"
echo -e "${GREEN}Quick start complete!${NC}"
echo -e "${BLUE}======================================================${NC}"
echo ""
echo "Next steps:"
echo "  - Read USAGE_EXAMPLES.md for more examples"
echo "  - Use ./benchmark_hashes.sh to test hash performance"
echo "  - Examine the extracted files in the hashes/ directory"
echo "  - Use 'make help' to see all available commands"
echo ""
