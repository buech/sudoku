## Explanation

Simple solver for 9x9 Sudokus in `C` with multiple backends.

## Requirements

- `C99` compiler
- [libcdlx](https://github.com/buech/cdlx)

## Compilation

The path to `libcdlx` should be specified in the makefile or from the command
line, for example:
```
$ make CDLXDIR=$HOME/Projects/cdlx
```

## Usage

The solver takes the Sudoku read from top left to bottom right as a continuous
string of 81 characters with `0` for empty positions as an argument or from
stdin. For example:
```
$ ./solver 300080000000700005100000000000000360002004000070000000000060130045200000000000800
```
For help:
```
$ ./solver -h
```

## Backends

Sudokus can be solved with different backends, specified with the `-b` option.
Right now, the following backends exist:
- `dlx` (default): Donald Knuth's [DLX
  algorithm](https://arxiv.org/abs/cs/0011047v1). Fastest and finds all possible
  solutions
- `bt`: Recursive backtracking. Finds one possible solution reasonably fast by
  trying all possibilities starting at the top left corner and backtracking in
  case of conflicts
- `dumb`: (Very) dumb elimination solver. This is just for fun and mimics a very
  simple "human" strategy of solving by building a list of all remaining
  possibilities and then filling and eliminating unique fields. Hence, it almost
  always fails to find a solution except for easy Sudokus.

Additional backends could easily be added.
