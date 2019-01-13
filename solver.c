#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_board(int *board) {
   for (int i = 0; i < 81; i++)
      printf("%1d", board[i]);
   putchar('\n');
}

int search(int *board, int pos) {
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

void usage(char *program_name) {
   printf(
"usage: %s [-h] SUDOKU\n\n", program_name);
   puts(
"Sudoku solver in C using backtracking\n\n"

"positional arguments:\n"
"  SUDOKU        Sudoku in the form of a continuous string read from\n"
"                left to right with 0 for empty cells, must have a\n"
"                length of at least 81 characters, additional\n"
"                characters are ignored\n"
"optional arguments:\n"
"  -h, --help    show this help message and exit"
   );
}

int main(int argc, char *argv[]) {

   int board[81];

   if (argc == 2) {
      if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
         usage(argv[0]);
         return EXIT_SUCCESS;
      }
      else {
         if (strlen(argv[1]) < 81) {
            fputs("Error: The sudoku has too few fields\n", stderr);
            usage(argv[0]);
            return EXIT_FAILURE;
         }
         else {
            if (strlen(argv[1]) > 81)
               fputs("Warning: The sudoku has too many fields. Additional fields will be ignored.\n", stderr);
            for (int i = 0; i < 81; ++i)
               board[i] = argv[1][i] >= '1' && argv[1][i] <= '9' ? argv[1][i]-'0' : 0;
         }
      }
   }
   else if (argc > 2) {
      fputs("Error: Too many arguments\n", stderr);
      usage(argv[0]);
      return EXIT_FAILURE;
   }
   else {
      fputs("Error: Too few arguments\n", stderr);
      usage(argv[0]);
      return EXIT_FAILURE;
   }

   if (search(board, 0)) {
      print_board(board);
   } else {
      puts("The puzzle is not solvable!");
   }

   return EXIT_SUCCESS;
}
