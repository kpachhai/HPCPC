EXES = serial_brute_force
F = passlist/simplewords.txt
A = passlist/test.txt
B = dictionary_attack
C = 10

D = d-a-leveldb-create-db
E = d-a-leveldb
F = d-a-leveldb-mpi

G = passlist/wordsforsimpletest.txt
J = passlist/hashFileToTest.txt
I = passlist/convertedHash.txt

P = 1
H = 1a1dc91c907325c69271ddf0c944bc72
M = 5

GCC = g++

all: $(EXES)
	$(GCC) -Wall -O3 -o $@ $^

mpi_brute_force:
	mpic++ mpi_brute_force.cpp -o $@

run_mpi_brute:
	mpirun -np $(P) ./mpi_brute_force $(H) $(M)

run_mpi_brute:
	mpirun -np $(P) ./mpi_brute_force $(H) $(M)

dic_attack_basic:
	$(GCC) -O3 -o $(B) dictionary_attack.cpp
	./dictionary_attack $(G) 16 $(J) 16 $(I)

dic_attack_db:
	$(GCC) -O3 -o $(D) d-a-leveldb-create-db.cpp leveldb/libleveldb.a -lpthread -I leveldb/include

dic_attack_db_exec:
	$(GCC) -O3 -o $(E) d-a-leveldb.cpp leveldb/libleveldb.a -lpthread -I leveldb/include
	./d-a-leveldb $(HASH)
	
dic_attack_db_exec_mpi:
	mpicxx d-a-leveldb-mpi.cpp -o $(F) leveldb/libleveldb.a -lpthread -I leveldb/include
	mpirun -np $(P) ./d-a-leveldb-mpi $(HASH)

test:
	python performance.py $(A) $(B) $(C) $(P)

clean:
	rm -f $(EXES)
	rm -f mpi_brute_force d-a-leveldb d-a-leveldb-create-db dictionary_attack d-a-leveldb-mpi 

love:
	@echo "not war"

