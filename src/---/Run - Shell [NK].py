#!/bin/bash

base=${1:-$ (basename $ (pwd) )}
dir=${1:-$ (dirname $ (pwd) )}

src_file="$dir/$base/$base.cpp"
in_file="$dir/$base/$base.in"
out_file="$dir/$base/$base.out"
bin_file="$dir/$base/$base"

g++ "$src_file" -std=c++17 -o "$bin_file"

"$bin_file" <"$in_file" >"$out_file"

rm "$bin_file"
