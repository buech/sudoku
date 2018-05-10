#!/usr/bin/env sh

parallel ./solver {= 's/\./0/g' =} :::: top95.txt

