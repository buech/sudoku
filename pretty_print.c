#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "string_to_board.h"

static void print_board(int *board) {
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

static void usage(char *program_name) {
   printf(
"usage: %s [-h] SUDOKU\n\n", program_name);
   puts(
"Pretty printer for Sudokus in string format\n\n"

"positional arguments:\n"
"  SUDOKU        Sudoku in the form of a continuous string read from\n"
"                left to right with 0 for empty cells, must have a\n"
"                length of at least 81 characters, additional\n"
"                characters are ignored\n"
"optional arguments:\n"
"  -h            show this help message and exit"
   );
}

int main(int argc, char **argv) {
   int opt;
   while ((opt = getopt(argc, argv, "h")) != -1) {
      switch (opt) {
         case 'h':
            usage(argv[0]);
            return EXIT_SUCCESS;

         case '?':
            return EXIT_FAILURE;
      }
   }
   argc -= optind;
   argv += optind - 1;

   int board[81];
   int err = 0;
   if (argc) {
      err = string_to_board(board, argv[1]);
      goto handle_err;
   } else {
      if (isatty(0)) {
         fputs("ERROR: Missing argument\n", stderr);
         return EXIT_FAILURE;
      } else {
         char buf[83];
         int n;
         n = read(0, buf, sizeof(buf));
         buf[strlen(buf)-1] = '\0';

         err = string_to_board(board, buf);
         goto handle_err;
      }
   }

handle_err:
   if (err == 1) {
      fputs("ERROR: The sudoku has too few fields\n", stderr);
      return EXIT_FAILURE;
   } else if (err == 2) {
      fputs("WARNING: The sudoku has too many fields, additional fields will be ignored\n", stderr);
   }

   print_board(board);

   return EXIT_SUCCESS;
}
