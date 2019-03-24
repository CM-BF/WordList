#!/bin/bash
name="wordlist.cpp"
cd ../src
out=${name:0:${#name}-4}".so"
g++ -std=c++11 -shared -fPIC -o $out $name
export LD_LIBRARY_PATH=./
python3 wordlist-gui.py
