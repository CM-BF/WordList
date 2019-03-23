#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -w -c -f inFile.txt

