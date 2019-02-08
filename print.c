#include <stdio.h>

void print_simple(int *board) {
   for (int i = 0; i < 81; i++)
      printf("%1d", board[i]);
   putchar('\n');
}

void print_pretty(int *board) {
   putchar('\n');
   for (int i = 0; i < 9; i++) {
      if (!(i % 3) && i)
         putchar('\n');
      for (int k = 9 * i; k < 9 * (i+1); k++) {
         if (!(k % 3))
            putchar(' ');
         if (board[k])
            printf("%2i", board[k]);
         else
            printf(" .");
      }
      putchar('\n');
   }
   putchar('\n');
}
