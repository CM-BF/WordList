#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -w -n 4 -f inFile.txt

