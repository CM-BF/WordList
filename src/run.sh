#!/bin/bash
name=$1
out=${name:0:${#name}-4}
g++ $name -o $out
echo "output to [$out]"
./$out
