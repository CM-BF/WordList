#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -w -f inFile.txt
