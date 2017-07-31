#!/bin/tcsh -fe
# This script starts unit tests of Runin.
make --directory=$GTEST/make || exit
make test  || exit
chmod 755 test.bin || exit
./test.bin || exit
