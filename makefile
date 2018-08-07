CFLAGS += -Wall -std=c99 -O3 -march=native
FC = gfortran
FCFLAGS += -Wall -O3 -march=native

all: c fort

c: solver dumb

fort: fsolver

fsolver: solver.f90
	$(FC) $(FCFLAGS) -o $@ $<

clean:
	rm -f solver fsolver dumb

.PHONY: all clean
