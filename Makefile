EXES = brute_force
F = passlist/simplewords.txt

all: $(EXES)
	g++ -Wall -O3 -o $@ $^

mpi_brute_force:
	mpicc mpi_brute_force.cpp  -o $@
convert:

clean:
	rm -f $(EXES)
	rm -f mpi_brute_force

love:
	@echo "not war"

