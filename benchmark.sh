#!/usr/bin/env sh

printf "Running C-solver...\n"
time cat top95.txt | sed 's/\./0/g' | xargs -L1 ./solver > /dev/null

printf "Running Fortran-solver...\n"
time cat top95.txt | sed 's/\./0/g' | xargs -L1 ./fsolver > /dev/null
