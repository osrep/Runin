#!/bin/tcsh -f

mkdir build && cd build
cmake .. -DTESTING_ENABLED=yes && make
test/RuninTests