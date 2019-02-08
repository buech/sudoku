CDLXDIR ?= ../cdlx

CFLAGS += -Wall -Wextra -pedantic -std=c99 -O3
CPPFLAGS += -I$(CDLXDIR)
CPPFLAGS += -MMD
LDFLAGS += -L$(CDLXDIR)
LDLIBS += -lcdlx

SRC = solver.c string_to_board.c print.c
SRC += backend_dlx.c
SRC += backend_backtracking.c
SRC += backend_dumb.c

OBJ := $(SRC:.c=.o)

all: solver

solver: $(OBJ)

-include $(wildcard *.d)

clean:
	rm -f *.o *.d solver

.PHONY: all clean
