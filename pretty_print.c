#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void usage(char *program_name) {
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

   print_board(board);

   return EXIT_SUCCESS;
}
