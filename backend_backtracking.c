static int search(int *board, int pos) {
   if (pos == 81)
      return 1;

   if (board[pos])
      return search(board, pos+1);

   int col = pos % 9;
   int row = pos / 9;
   unsigned short valid = 0;

   for (int i = 0; i < 9; ++i) {
      valid |= 1 << (board[9 * row + i] - 1);
      valid |= 1 << (board[9 * i + col] - 1);
   }

   col = col / 3 * 3;
   row = row / 3 * 3;

   for (int i = row; i < row + 3; ++i)
      for (int j = col; j < col + 3; ++j)
         valid |= 1 << (board[9 * i + j] - 1);

   valid = ~valid;

   for (board[pos] = 1; board[pos] <= 9; board[pos]++, valid >>= 1) {
      if (valid & 1) {
         if (search(board, pos+1))
            return 1;
      }
   }

   board[pos] = 0;
   return 0;
}

int solve_backtrack(int *board) {
   if (search(board, 0))
      return 1;
   else
      return 0;
}
