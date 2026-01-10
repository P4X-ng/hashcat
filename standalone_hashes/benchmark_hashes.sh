#!/usr/bin/env bash
##
## Simple Hash Benchmarking Script
## Uses hashcat in benchmark mode for individual hash algorithms
##

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Get the script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
HASHCAT_ROOT="$(dirname "$SCRIPT_DIR")"
HASHCAT_BIN="$HASHCAT_ROOT/hashcat"

# Common hash modes that correspond to our extracted functions
declare -A HASH_MODES
HASH_MODES=(
  [MD4]="900"
  [MD5]="0"
  [SHA1]="100"
  [SHA224]="1300"
  [SHA256]="1400"
  [SHA384]="10800"
  [SHA512]="1700"
  [RIPEMD160]="6000"
  [Whirlpool]="6100"
  [BLAKE2b-512]="600"
  [GOST]="6900"
  [scrypt]="8900"
)

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}Hashcat Hash Function Benchmarking${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

# Check if hashcat binary exists
if [ ! -f "$HASHCAT_BIN" ]; then
  echo -e "${YELLOW}Hashcat binary not found at: $HASHCAT_BIN${NC}"
  echo -e "${YELLOW}Building hashcat...${NC}"
  echo ""
  
  cd "$HASHCAT_ROOT"
  if make; then
    echo -e "${GREEN}Hashcat built successfully!${NC}"
    echo ""
  else
    echo -e "${RED}Failed to build hashcat${NC}"
    echo "Please build hashcat manually first: cd $HASHCAT_ROOT && make"
    exit 1
  fi
fi

# Parse command line arguments
if [ $# -eq 0 ]; then
  echo -e "${CYAN}Available hash functions to benchmark:${NC}"
  echo ""
  for hash in "${!HASH_MODES[@]}"; do
    echo -e "  ${GREEN}$hash${NC} (mode ${HASH_MODES[$hash]})"
  done | sort
  echo ""
  echo -e "${YELLOW}Usage:${NC} $0 [hash_name1] [hash_name2] ..."
  echo -e "${YELLOW}Example:${NC} $0 MD5 SHA256 SHA512"
  echo ""
  echo -e "Or run all benchmarks: $0 all"
  exit 0
fi

# Function to benchmark a single hash
benchmark_hash() {
  local hash_name=$1
  local hash_mode=${HASH_MODES[$hash_name]}
  
  if [ -z "$hash_mode" ]; then
    echo -e "${RED}Unknown hash: $hash_name${NC}"
    return 1
  fi
  
  echo -e "${CYAN}========================================${NC}"
  echo -e "${CYAN}Benchmarking: $hash_name (mode $hash_mode)${NC}"
  echo -e "${CYAN}========================================${NC}"
  
  "$HASHCAT_BIN" -b -m "$hash_mode" --machine-readable 2>/dev/null | grep -v "^#" || \
  "$HASHCAT_BIN" -b -m "$hash_mode" 2>&1 | grep -E "(Speed\.|Hashrate)"
  
  echo ""
}

# Benchmark requested hashes
if [ "$1" = "all" ]; then
  echo -e "${GREEN}Running benchmarks for all hash functions...${NC}"
  echo ""
  
  for hash in "${!HASH_MODES[@]}"; do
    benchmark_hash "$hash"
  done | sort
else
  for hash_arg in "$@"; do
    # Convert to uppercase for matching
    hash_upper=$(echo "$hash_arg" | tr '[:lower:]' '[:upper:]')
    benchmark_hash "$hash_upper"
  done
fi

echo -e "${GREEN}Benchmarking complete!${NC}"
