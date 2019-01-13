
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "string_to_board.h"
#include "backends.h"

void print_board(int *board) {
   for (int i = 0; i < 81; i++)
      printf("%1d", board[i]);
   putchar('\n');
}

void usage(char *program_name) {
   printf(
"usage: %s [-h] [-b BACKEND] SUDOKU\n\n", program_name);
   puts(
"Sudoku solver in C with multiple backends\n\n"

"positional arguments:\n"
"  SUDOKU        Sudoku in the form of a continuous string read from\n"
"                left to right with 0 for empty cells, must have a\n"
"                length of at least 81 characters, additional\n"
"                characters are ignored\n"
"optional arguments:\n"
"  -h            Show this help message and exit\n"
"  -b BACKEND    Backend (dlx/bt/dumb), default is dlx\n"
   );
}

enum Backend {
   DLX,
   BT,
   DUMB
};

int main(int argc, char **argv) {
   int backend;
   int opt;
   while ((opt = getopt(argc, argv, "hb:")) != -1) {
      switch (opt) {
         case 'b':
            if (!strcmp(optarg, "dlx"))
               backend = DLX;
            else if (!strcmp(optarg, "bt"))
               backend = BT;
            else if (!strcmp(optarg, "dumb"))
               backend = DUMB;
            else {
               printf("WARNING: Unknown backend %s, using dlx\n", optarg);
               backend = DLX;
            }
            break;

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
   if (argc) {
      int err = string_to_board(board, argv[1]);
      if (err == 1) {
         fputs("ERROR: The sudoku has too few fields\n", stderr);
         return EXIT_FAILURE;
      } else if (err == 2) {
         fputs("WARNING: The sudoku has too many fields, additional fields will be ignored\n", stderr);
      }
   } else {
      // TODO: read from stdin
      fputs("ERROR: Missing argument\n", stderr);
      return EXIT_FAILURE;
   }

   // Number of solutions, though only DLX is able to find multiple solutions
   // the other backends just return 1 in case they found one
   int nsol = 0;
   switch (backend) {
      case DLX:
         nsol = solve_dlx(board);
         break;

      case BT:
         nsol = solve_backtrack(board);
         break;

      case DUMB:
         nsol = solve_dumb(board);
         break;
   }

   if (nsol) {
      // DLX backend already prints all solutions on the way
      if (backend != DLX)
         print_board(board);
   } else {
      puts("Could not find a solution");
   }

   return EXIT_SUCCESS;
}
