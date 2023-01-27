#!/bin/bash

# Get the path to the source file and upper bound letter as arguments
source_file=$1
upper_bound=$2

# Create a for loop to iterate through the letters a to upper_bound
for letter in {a..$upper_bound}
do
    # Create a directory with the current letter as its name
    mkdir $letter

    # Enter the directory
    cd $letter

    # Create the input and output files with the same name as the directory
    touch "$letter.in"
    touch "$letter.out"

    # Create a CPP file with the same name as the directory
    touch "$letter.cpp"

    # Copy the content of the source file to the CPP file
    cat $source_file > "$letter.cpp"

    # Go back to the parent directory
    cd ..
done
