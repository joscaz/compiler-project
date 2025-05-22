#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Make sure the compiler is built
echo -e "${YELLOW}Building compiler...${NC}"
make clean
make
echo ""

# Function to run a test case
run_test() {
    local testfile="$1"
    local testname=$(basename "$testfile" .txt)
    
    echo -e "${YELLOW}Testing ${testname}...${NC}"
    
    echo "Test input:"
    cat "$testfile"
    echo ""
    
    echo "Compiler output:"
    ./babyduck < "$testfile"
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Test passed!${NC}"
    else
        echo -e "${RED}✗ Test failed!${NC}"
    fi
    echo "--------------------------------"
}

# Run test for conditional and loop statements
echo -e "${YELLOW}Running tests for entrega4...${NC}"
echo "--------------------------------"

run_test "testcases/entrega4/test_conditional_loop.txt"

echo -e "${YELLOW}All tests completed.${NC}" 