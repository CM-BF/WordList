#!/bin/bash
cd ../src
make
./main -c -h a -t s -f ../data/inFile.txt
