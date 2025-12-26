#!/bin/bash
set -e

g++ -std=gnu++23 -O2 -march=native src/solution.cpp -o oxc_router
echo "Build successful: ./oxc_router"



# Make executable:
# chmod +x build.sh
