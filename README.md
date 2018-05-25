## Explanation

Simple backtracking solvers for 9x9 Sudokus in `C`, `python` and `Fortran`
inspired by the [Rosetta Code example](https://rosettacode.org/wiki/Sudoku#C).
The benchmark script uses the "Top 95" examples from [Peter Norvigs
essay](http://norvig.com/sudoku.html).  
Brute-force backtracking seems to work quite well for normal 9x9 grids, even
Sudokus designed to be hard to brute-force only take some seconds to solve, like
the example below:

```
$ time ./solver 000000000000003085001020000000507000004000100090000000500000073002010000000040009
Input:
  . . .  . . .  . . .
  . . .  . . 3  . 8 5
  . . 1  . 2 .  . . .

  . . .  5 . 7  . . .
  . . 4  . . .  1 . .
  . 9 .  . . .  . . .

  5 . .  . . .  . 7 3
  . . 2  . 1 .  . . .
  . . .  . 4 .  . . 9

Solution:
  9 8 7  6 5 4  3 2 1
  2 4 6  1 7 3  9 8 5
  3 5 1  9 2 8  7 4 6

  1 2 8  5 3 7  6 9 4
  6 3 4  8 9 2  1 5 7
  7 9 5  4 6 1  8 3 2

  5 1 9  2 8 6  4 7 3
  4 7 2  3 1 9  5 6 8
  8 6 3  7 4 5  2 1 9

real	0m2.329s
user	0m2.324s
sys	0m0.003s
```

## Requirements

- a `C` compiler for the `C` version
- `python` (2 or 3) for the `python` version
- a `Fortran` compiler for the `Fortran` version (tested with `gfortran`)

## Compilation

Self-explanatory:  
```
$ make c
```
to compile the `C` version,
```
$ make fort
```
to compile the `Fortran` version or just `make` to compile both.

## Usage

The solvers take the Sudoku read from top left to bottom right as a continuous
string of 81 characters with `0` for empty positions. For example (or see the
example above):

```
$ ./solver 300080000000700005100000000000000360002004000070000000000060130045200000000000800
```
