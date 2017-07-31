#!/bin/tcsh -fe
# This script starts unit tests of Runin.

setenv RECENT_DIR pwd
cd $GTEST
make
cd $RECENT_DIR
make test
./test.bin
