#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "string_to_board.h"
#include "backends.h"
#include "print.h"

static void usage(char *program_name) {
   printf(
"usage: %s [-h] [-b BACKEND] SUDOKU\n\n"

"Sudoku solver in C with multiple backends\n\n"

"positional arguments:\n"
"  SUDOKU        Sudoku in the form of a continuous string read from\n"
"                left to right with 0 for empty cells, must have a\n"
"                length of at least 81 characters, additional\n"
"                characters are ignored\n"
"optional arguments:\n"
"  -b BACKEND    Backend (dlx/bt/dumb), default is dlx\n"
"  -h            Show this help message and exit\n"
"  -p            Print input to output without solving\n"
"  -P            Print in square form\n"
   ,program_name);
}

int main(int argc, char **argv) {
   // Set up print function pointer
   print_board = print_simple;
   int print = 0;
   int backend;
   int opt;
   while ((opt = getopt(argc, argv, "b:hpP")) != -1) {
      switch (opt) {
         case 'b':
            if (!strcmp(optarg, "dlx"))
               backend = DLX;
            else if (!strcmp(optarg, "bt"))
               backend = BT;
            else if (!strcmp(optarg, "dumb"))
               backend = DUMB;
            else {
               fprintf(stderr, "WARNING: Unknown backend %s, using dlx\n", optarg);
               backend = DLX;
            }
            break;

         case 'h':
            usage(argv[0]);
            return EXIT_SUCCESS;

         case 'p':
            print = 1;
            break;

         case 'P':
            print_board = print_pretty;
            break;

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
         char buf[82];
         int n;
         n = fread(buf, sizeof(char), sizeof(buf), stdin);
         buf[n-1] = '\0';

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

   if (print) {
      print_board(board);
      return EXIT_SUCCESS;
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
