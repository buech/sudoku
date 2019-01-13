#!/usr/bin/env sh

printf "Running C-solver (backtracking) ...\n"
time sed 's/\./0/g' top95.txt | xargs -L1 ./solver -b bt > /dev/null

printf "Running Fortran-solver ...\n"
time sed 's/\./0/g' top95.txt | xargs -L1 ./fsolver > /dev/null

printf "Running C-solver (dlx) ...\n"
time sed 's/\./0/g' top95.txt | xargs -L1 ./solver -b dlx > /dev/null
