#ifndef BACKENDS_H
#define BACKENDS_H

enum Backend {
   DLX,
   BT,
   DUMB
};

int solve_dlx(int *board);
int solve_backtracking(int *board);
int solve_dumb(int *board);

#endif
