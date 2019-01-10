#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

void print_board(int *board) {
   for(int i = 0; i < 9; i++) {
      if(!(i % 3) && i)
         putchar('\n');
      for(int k = 9 * i; k < 9 * (i+1); k++) {
         if(!(k % 3))
            putchar(' ');
         board[k] ? printf("%2i", board[k]) : printf(" .");
      }
      putchar('\n');
   }
   putchar('\n');
}

void printb(unsigned short n) {
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

   for(; i > 0; i--)
      printf("0");
}

/*
void print_pool(unsigned short *board) {
   for(int i = 0; i < 9; i++) {
      if(!(i % 3) && i)
         putchar('\n');
      for(int k = 9 * i; k < 9 * (i+1); k++) {
         if(!(k % 3))
            putchar(' ');
         board[k] ? printb(board[k]) : printf("         .");
      }
      putchar('\n');
   }
   putchar('\n');
}
*/

void fill(unsigned short *pool, int *board) {
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

void cancel(unsigned short *pool, int pos, int digit) {
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
int pot(unsigned short x) {
   return ((x != 0) && ((x & (~x + 1)) == x));
}

int next_pos(unsigned short *pool) {
   for (int pos = 0; pos < 81; pos++) {
      if (pot(pool[pos])) {
         return pos;
      }
   }
   return -1;
}

int which_pot(unsigned short x) {
   int i;
   unsigned short n;

   for (i = 0, n=x; ~n & 1; i++, n >>= 1);

   return i;
}

void search(int *board) {
   unsigned short pool[81] = {0};
   //print_pool(pool);
   fill(pool, board);
   //puts("Initial pool:");
   //print_pool(pool);

   int pos = next_pos(pool);
   while (pos >= 0) {
      board[pos] = which_pot(pool[pos]) + 1;
      cancel(pool, pos, board[pos] - 1);

      //puts("Pool after canceling");
      //print_pool(pool);

      //print_board(board);
      //usleep(1000000);

      pos = next_pos(pool);
   }
}

void usage(char *program_name) {
   printf(
"usage: %s [-h] SUDOKU\n\n", program_name);
   puts(
"Sudoku solver in C using dumb elimination\n\n"

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

   if(argc == 2) {
      if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
         usage(argv[0]);
         return EXIT_SUCCESS;
      }
      else {
         if(strlen(argv[1]) < 81) {
            fputs("Error: The sudoku has too few fields\n", stderr);
            usage(argv[0]);
            return EXIT_FAILURE;
         }
         else {
            if(strlen(argv[1]) > 81)
               fputs("Warning: The sudoku has too many fields. Additional fields will be ignored.\n", stderr);
            for(int i = 0; i < 81; ++i)
               board[i] = (argv[1])[i] >= '1' && (argv[1])[i] <= '9' ? (argv[1])[i]-'0' : 0;
         }
      }
   }
   else if(argc > 2) {
      fputs("Error: Too many arguments\n", stderr);
      usage(argv[0]);
      return EXIT_FAILURE;
   }
   else {
      fputs("Error: Too few arguments\n", stderr);
      usage(argv[0]);
      return EXIT_FAILURE;
   }

   puts("Input:");
   print_board(board);

   search(board);

   puts("Solution:");
   print_board(board);

   return EXIT_SUCCESS;
}
