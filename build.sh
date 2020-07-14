#!/bin/tcsh -fe

########## compiling code #########

# without test files
mkdir build && cd build
cmake .. && make



# with test files - Disabled due to lack of central gtest installation
# make test
# ./test.bin
