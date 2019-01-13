#include <string.h>

int string_to_board(int *board, char *string) {
   int err = 0;
   if (strlen(string) < 81) {
      return 1;
   } else {
      if (strlen(string) > 81)
         err = 2;
      for (int i = 0; i < 81; i++)
         board[i] = string[i] >= '1' && string[i] <= '9' ? string[i]-'0' : 0;
   }

   return err;
}
