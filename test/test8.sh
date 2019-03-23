#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -n 3 -c -h y -t d -f inFile_old.txt

