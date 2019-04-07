#!/bin/bash
make
export LD_LIBRARY_PATH=./
./main
lcov -d . -t 'Test' -o 'Test.info' -b . -c
genhtml -o ../cover/ Test.info