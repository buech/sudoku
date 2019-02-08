#include <stdio.h>

#include "dlx.h"
#include "print.h"

static void print_sol(dlx_t *d) {
   int board[81] = {0};
   int min, val;
   node_t *minRow, *row;
   sol_t *cur;
   for (cur = d->s; cur; cur = cur->next) {
      minRow = cur->row;
      min = minRow->c->n;
      for (row = minRow->r; row != minRow; row = row->r) {
         val = row->c->n;
         if (val < min) {
            min = val;
            minRow = row;
         }
      }
      board[9 * (minRow->c->n / 9) + (minRow->c->n % 9)] = (minRow->r->c->n) % 9 + 1;
   }

   print_board(board);
}

int solve_dlx(int *board) {
   int nsol = 0;
   dlx_t *d = new_dlx(324);

   for (int row = 0, i = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++, i++) {
         int block = row / 3 * 3 + col / 3;
         int n = board[i];
         if (n) {
            int con[324] = {0};
            con[i] = 1;
            con[ 81 + 9 * row   + n - 1] = 1;
            con[162 + 9 * col   + n - 1] = 1;
            con[243 + 9 * block + n - 1] = 1;
            add_row(d, 324, con);
         } else {
            for (n = 0; n < 9; n++) {
               int con[324] = {0};
               con[i] = 1;
               con[ 81 + 9 * row   + n] = 1;
               con[162 + 9 * col   + n] = 1;
               con[243 + 9 * block + n] = 1;
               add_row(d, 324, con);
            }
         }
      }
   }

   solve(d, print_sol);
   nsol = d->nsol;

   free_dlx(d);

   return nsol;
}
