#!/bin/bash

for x in {a..j}
do
    mkdir -p ./${x}
    cd ./${x}
    touch ${x}.cpp
    touch ${x}.in
    touch ${x}.out
    cp ../template.cpp ${x}.cpp
    cd ..
done
