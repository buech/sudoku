FC ?= gfortran

CFLAGS += -Wall -Wextra -pedantic -std=c99 -O3 -march=native
FFLAGS += -Wall -Wextra -pedantic -std=f2003 -O3 -march=native

CDLX_DIR = ../cdlx

CPPFLAGS += -I$(CDLX_DIR)
CPPFLAGS += -MMD
LDFLAGS += -L$(CDLX_DIR)
LDLIBS += -lcdlx

FEXEC = fsolver

SRC = solver.c string_to_board.c
SRC += backend_dlx.c
SRC += backend_backtracking.c
SRC += backend_dumb.c

OBJ := $(SRC:.c=.o)

all: c fort pretty_print

c: solver

solver: $(OBJ)

pretty_print: string_to_board.o

fort: $(FEXEC)

$(FEXEC): solver.f90
	$(FC) $(FFLAGS) -o $@ $<

-include $(wildcard *.d)

clean:
	rm -f *.o *.d $(FEXEC) solver pretty_print

.PHONY: all clean
