static void fill(unsigned short *pool, int *board) {
   for (int pos = 0; pos < 81; pos++) {
      if (board[pos])
         continue;

      int col = pos % 9;
      int row = pos / 9;
      unsigned short valid = 0;

      for (int i = 0; i < 9; i++) {
         valid |= 1 << (board[9 * row + i] - 1);
         valid |= 1 << (board[9 * i + col] - 1);
      }

      col = col / 3 * 3;
      row = row / 3 * 3;

      for (int i = row; i < row + 3; i++)
         for (int j = col; j < col + 3; j++)
            valid |= 1 << (board[9 * i + j] - 1);

      pool[pos] = ~valid & 0x1ff;
   }
}

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
   unsigned short n;

   for (i = 0, n=x; ~n & 1; i++, n >>= 1);

   return i;
}

int solve_dumb(int *board) {
   unsigned short pool[81] = {0};
   fill(pool, board);

   int pos = next_pos(pool);
   while (pos >= 0) {
      board[pos] = which_pot(pool[pos]) + 1;
      cancel(pool, pos, board[pos] - 1);

      pos = next_pos(pool);
   }

   return 1;
}
