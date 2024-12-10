#!/bin/bash
part=$1
clang++ -Wno-unqualified-std-cast-call -std=c++20 "${part}.cpp" -lket -O0 -g -o "./${part}";
./$part
