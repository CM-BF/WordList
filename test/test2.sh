#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -c -f inFile.txt

