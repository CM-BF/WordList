#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -w -h a -t s -f inFile.txt

