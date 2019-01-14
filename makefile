CDLX_DIR = ../cdlx

CFLAGS += -Wall -Wextra -pedantic -std=c99 -O3
CPPFLAGS += -I$(CDLX_DIR)
CPPFLAGS += -MMD
LDFLAGS += -L$(CDLX_DIR)
LDLIBS += -lcdlx

SRC = solver.c string_to_board.c
SRC += backend_dlx.c
SRC += backend_backtracking.c
SRC += backend_dumb.c

OBJ := $(SRC:.c=.o)

all: solver pretty_print

solver: $(OBJ)

pretty_print: pretty_print.o string_to_board.o

-include $(wildcard *.d)

clean:
	rm -f *.o *.d solver pretty_print

.PHONY: all clean
