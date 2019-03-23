#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -n 5 -h a -t s -f inFile.txt

