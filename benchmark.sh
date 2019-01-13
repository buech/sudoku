#!/usr/bin/env sh

printf "Running C-solver (backtracking) ...\n"
time cat top95.txt | sed 's/\./0/g' | xargs -L1 ./solver -b bt > /dev/null

printf "Running Fortran-solver ...\n"
time cat top95.txt | sed 's/\./0/g' | xargs -L1 ./fsolver > /dev/null

printf "Running C-solver (dlx) ...\n"
time cat top95.txt | sed 's/\./0/g' | xargs -L1 ./solver -b dlx > /dev/null
