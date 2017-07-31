#!/bin/tcsh -fe
# This script starts unit tests of Runin.
make --directory=$GTEST/make || exit
cmake -E chdir $GTEST  || exit
make --directory=$GTEST || exit
make test
chmod 755 test.bin || exit
./test.bin || exit
