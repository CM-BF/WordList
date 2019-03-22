#!/bin/bash
name=$1
out=${name:0:${#name}-4}
g++ -std=c++11 $name -o $out
echo "output to [$out]"
./$out -h t -t f  -c inFile_old.txt
