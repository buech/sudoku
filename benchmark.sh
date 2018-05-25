#!/usr/bin/env sh

echo "Running C-solver..."
time cat top95.txt | sed 's/\./0/g' | xargs -L1 ./solver > /dev/null

echo "Running Fortran-solver..."
time cat top95.txt | sed 's/\./0/g' | xargs -L1 ./fsolver > /dev/null
