#!/bin/tcsh -fe

########## compiling code #########

# without test files
make

# with test files
make test
test/test.bin
