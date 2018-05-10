#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division, print_function
from time import sleep
import argparse

animate = False
delay = 0.1

def print_board(board):
    for i in range(9):
        if not i % 3 and i:
            print()
        for k in range(9 * i, 9 * (i+1)):
            if not k % 3:
                print(' ', end='')
            print(' .', end='') if board[k] == 0 else print('%2d'%(board[k]), end='')
        print()
    print()

def search(board, pos):
    if pos == 81:
        return True

    if board[pos]:
        return search(board, pos+1)

    col = pos % 9
    row = pos // 9
    invalid = 0

    for i in range(9):
        invalid |= 1 << board[9 * row + i]
        invalid |= 1 << board[9 * i + col]

    col = col // 3 * 3
    row = row // 3 * 3

    for i in range(row, row + 3):
        for j in range(col, col + 3):
            invalid |= 1 << board[9 * i + j]

    invalid = invalid >> 1

    for i in range(1, 10):
        if not (invalid & 1):
            board[pos] = i
            if animate:
                print_board(board)
                print()
                sleep(delay)
            if search(board, pos+1):
                return 1
        invalid = invalid >> 1

    board[pos] = 0
    return False


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Sudoku solver in python using backtracking')
    parser.add_argument('sudoku', type=str, help='Sudoku in the form of a continuous string read from left to right with 0 for empty positions')
    parser.add_argument('-a', '--animate', action='store_true', help='Display each step of the solving process')
    parser.add_argument('-d', '--delay', type=float, default=0.1, help='Animation delay in seconds')

    args = parser.parse_args()

    if args.animate:
        animate = True
        delay = args.delay

    board = list(map(int, list(args.sudoku.replace(' ','').replace('\n',''))))
    print('Input:')
    print_board(board)

    if search(board, 0):
        print('Solution:')
        print_board(board)
    else:
        print('The puzzle is not solvable!')

