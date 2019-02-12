#ifdef DEBUG
#include <stdio.h>
#include <unistd.h>
#endif

static void fill(unsigned short *pool, int *board) {
   for (int pos = 0; pos < 81; pos++) {
      if (board[pos])
         continue;

      int col = pos % 9;
      int row = pos / 9;
      unsigned short valid = 0;

      for (int i = 0; i < 9; ++i) {
         int a = board[9 * row + i];
         int b = board[9 * i + col];
         if (a)
            valid |= 1 << (a - 1);
         if (b)
            valid |= 1 << (b - 1);
      }

      col = col / 3 * 3;
      row = row / 3 * 3;

      for (int i = row; i < row + 3; ++i) {
         for (int j = col; j < col + 3; ++j) {
            int a = board[9 * i + j];
            if (a)
               valid |= 1 << (a - 1);
         }
      }

      pool[pos] = ~valid & 0x1ff;
   }
}

#ifdef DEBUG
void print_bin(unsigned short n) {
   printf(" ");
   int i = 9;
   while (n) {
       if (n & 1)
           printf("1");
       else
           printf("0");

       n >>= 1;
       i--;
   }

   for (; i > 0; i--)
      printf("0");
}

void print_pool(unsigned short *board) {
   for (int i = 0; i < 9; i++) {
      if (!(i % 3) && i)
         putchar('\n');
      for (int k = 9 * i; k < 9 * (i+1); k++) {
         if (!(k % 3))
            putchar(' ');
         if (board[k])
            print_bin(board[k]);
         else
            printf("         .");
      }
      putchar('\n');
   }
   putchar('\n');
}
#endif

static void cancel(unsigned short *pool, int pos, int digit) {
   int col = pos % 9;
   int row = pos / 9;
   unsigned short mask = ~(1 << digit);

   for (int i = 0; i < 9; i++) {
      pool[9 * row + i] &= mask;
      pool[9 * i + col] &= mask;
   }

   col = col / 3 * 3;
   row = row / 3 * 3;

   for (int i = row; i < row + 3; i++)
      for (int j = col; j < col + 3; j++)
         pool[9 * i + j] &= mask;
}

// Check if x is a power of two
// i.e. has only one non-zero nibble
// i.e. has only one possible entry
static int pot(unsigned short x) {
   return ((x != 0) && ((x & (~x + 1)) == x));
}

static int next_pos(unsigned short *pool) {
   for (int pos = 0; pos < 81; pos++) {
      if (pot(pool[pos])) {
         return pos;
      }
   }
   return -1;
}

static int which_pot(unsigned short x) {
   int i;
   for (i = 0; ~x & 1; i++, x >>= 1);

   return i;
}

int solve_dumb(int *board) {
   unsigned short pool[81] = {0};
   fill(pool, board);

   int pos = next_pos(pool);
   while (pos >= 0) {
      board[pos] = which_pot(pool[pos]) + 1;
      cancel(pool, pos, board[pos] - 1);

#ifdef DEBUG
      puts("Pool after canceling");
      print_pool(pool);

      usleep(500000);
#endif

      pos = next_pos(pool);
   }

   return 1;
}
