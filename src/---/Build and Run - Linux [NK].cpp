#!/bin/bash

# Get the name of the current directory
dir_name=$(basename $(pwd))

# Set the names of the input and output files
in_file="$dir_name.in"
out_file="$dir_name.out"

# Compile the CPP file
g++ "$dir_name.cpp" -o "$dir_name"

# Run the compiled program, redirecting input and output
./"$dir_name" < "$in_file" > "$out_file"

# Delete the binary executable
rm "$dir_name"