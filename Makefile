EXES = brute_force
F = passlist/simplewords.txt
A = passlist/test.txt
B = dictionary_attack
C = 10

all: $(EXES)
	g++ -Wall -O3 -o $@ $^

mpi_brute_force:
	mpicc mpi_brute_force.cpp  -o $@

test:
	python performance.py $(A) $(B) $(C)

clean:
	rm -f $(EXES)
	rm -f mpi_brute_force

love:
	@echo "not war"

