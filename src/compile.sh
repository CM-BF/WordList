#!/bin/bash
name=$1
out=${name:0:${#name}-4}
g++ -std=c++11 $name -o $out

