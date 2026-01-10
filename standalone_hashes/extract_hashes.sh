#!/usr/bin/env bash
##
## Standalone Hash Function Extractor
## Extracts hash function implementations from hashcat's OpenCL directory
##

# Get the script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
HASHCAT_ROOT="$(dirname "$SCRIPT_DIR")"
OPENCL_DIR="$HASHCAT_ROOT/OpenCL"
OUTPUT_DIR="$SCRIPT_DIR/hashes"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}Hashcat Standalone Hash Extractor${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

# Check if OpenCL directory exists
if [ ! -d "$OPENCL_DIR" ]; then
  echo -e "${RED}Error: OpenCL directory not found at $OPENCL_DIR${NC}"
  exit 1
fi

# Create output directory
mkdir -p "$OUTPUT_DIR"

echo -e "${GREEN}Extracting hash functions from: $OPENCL_DIR${NC}"
echo -e "${GREEN}Output directory: $OUTPUT_DIR${NC}"
echo ""

# Counter for files
count_h=0
count_cl=0

# Copy hash header files (.h)
echo -e "${YELLOW}Copying hash header files (.h)...${NC}"
for file in "$OPENCL_DIR"/inc_hash_*.h; do
  if [ -f "$file" ]; then
    filename=$(basename "$file")
    cp "$file" "$OUTPUT_DIR/"
    echo "  ✓ $filename"
    ((count_h++))
  fi
done

echo ""

# Copy hash implementation files (.cl)
echo -e "${YELLOW}Copying hash implementation files (.cl)...${NC}"
for file in "$OPENCL_DIR"/inc_hash_*.cl; do
  if [ -f "$file" ]; then
    filename=$(basename "$file")
    cp "$file" "$OUTPUT_DIR/"
    echo "  ✓ $filename"
    ((count_cl++))
  fi
done

echo ""
echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}Extraction Complete!${NC}"
echo -e "${GREEN}========================================${NC}"
echo -e "Copied ${BLUE}$count_h${NC} header files (.h)"
echo -e "Copied ${BLUE}$count_cl${NC} implementation files (.cl)"
echo -e "Total: ${BLUE}$((count_h + count_cl))${NC} files"
echo ""
echo -e "Hash functions extracted to: ${BLUE}$OUTPUT_DIR${NC}"
echo ""
echo -e "${YELLOW}Tip:${NC} Run ./list_hashes.sh to see all available hash functions"
