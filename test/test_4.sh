#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -h e -t s -f inFile_big.txt

