CFLAGS += -Wall -std=c99 -O3 -march=native
FC = gfortran
FCFLAGS += -Wall -O3 -march=native

all: c fort

c: solver

fort: fsolver

solver: solver.c

fsolver: solver.f90
	$(FC) $(FCFLAGS) -o $@ $<

clean:
	rm -f solver fsolver

.PHONY: all clean
