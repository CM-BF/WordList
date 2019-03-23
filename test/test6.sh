#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -c -h a -t s -f inFile.txt
