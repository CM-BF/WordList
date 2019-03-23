#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -n 6 -f inFile_big.txt

