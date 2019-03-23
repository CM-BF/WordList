#!/bin/bash
cd ../src
./compile.sh wordlist.cpp
./wordlist -n 4 -c -h y -t d -f input.txt

