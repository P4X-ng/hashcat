#!/usr/bin/env bash
##
## List Available Hash Functions
## Shows all hash functions available in hashcat
##

# Get the script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
HASHCAT_ROOT="$(dirname "$SCRIPT_DIR")"
OPENCL_DIR="$HASHCAT_ROOT/OpenCL"

# Colors for output
BLUE='\033[0;34m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}Available Hash Functions in Hashcat${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

# Count hash functions
count=0

echo -e "${GREEN}Hash Algorithm${NC}              ${YELLOW}Header File${NC}                ${YELLOW}Implementation File${NC}"
echo "--------------------------------------------------------------------------------"

# Check if any hash files exist
if ! ls "$OPENCL_DIR"/inc_hash_*.h 1> /dev/null 2>&1; then
  echo -e "${YELLOW}No hash header files found in $OPENCL_DIR${NC}"
  exit 1
fi

# List all hash functions
for header in "$OPENCL_DIR"/inc_hash_*.h; do
  if [ -f "$header" ]; then
    ((count++))
    
    # Extract hash name
    header_file=$(basename "$header")
    hash_name=$(echo "$header_file" | sed 's/inc_hash_//' | sed 's/.h//' | tr '[:lower:]' '[:upper:]')
    
    # Check for corresponding .cl file
    cl_file="${header%.h}.cl"
    if [ -f "$cl_file" ]; then
      cl_filename=$(basename "$cl_file")
      echo -e "${GREEN}$(printf '%-24s' "$hash_name")${NC} $header_file    $cl_filename"
    else
      echo -e "${GREEN}$(printf '%-24s' "$hash_name")${NC} $header_file    ${YELLOW}(no .cl file)${NC}"
    fi
  fi
done

echo ""
echo -e "${BLUE}Total: $count hash functions available${NC}"
echo ""
echo -e "${YELLOW}To extract these files, run:${NC} ./extract_hashes.sh"
