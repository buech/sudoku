#!/usr/bin/env sh

echo "Running C-solver..."
time parallel ./solver {= 's/\./0/g' =} :::: top95.txt > /dev/null

echo "Running Fortran-solver..."
time parallel ./fsolver {= 's/\./0/g' =} :::: top95.txt > /dev/null

