CFLAGS += -Wall -Wextra -pedantic -std=c99 -O3 -march=native
FC = gfortran
FFLAGS += -Wall -Wextra -pedantic -std=f2003 -O3 -march=native

CEXEC = solver dumb pretty_print
FEXEC = fsolver

all: c fort

c: $(CEXEC)

fort: $(FEXEC)

fsolver: solver.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	rm -f $(CEXEC) $(FEXEC)

.PHONY: all clean
