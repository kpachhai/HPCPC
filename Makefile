EXES = serial_brute_force
F = passlist/simplewords.txt
A = passlist/test.txt
B = dictionary_attack
C = 10

D = d-a-leveldb-create-db
E = d-a-leveldb

P = 2
H = 1a1dc91c907325c69271ddf0c944bc72
M = 5

GCC = g++

all: $(EXES)
	$(GCC) -Wall -O3 -o $@ $^

mpi_brute_force:
	mpic++ mpi_brute_force.cpp -o $@

run_mpi_brute:
	mpirun -np $(P) ./mpi_brute_force $(H) $(M)

dic_attack_basic:
	$(GCC) -O3 -o $(B) dictionary_attack.cpp

dic_attack_db:
	$(GCC) -O3 -o $(D) d-a-leveldb-create-db.cpp leveldb/libleveldb.a -lpthread -I leveldb/include

dic_attack_db_exec:
	$(GCC) -O3 -o $(E) d-a-leveldb.cpp leveldb/libleveldb.a -lpthread -I leveldb/include

test:
	python performance.py $(A) $(B) $(C)

clean:
	rm -f $(EXES)
	rm -f mpi_brute_force d-a-leveldb d-a-leveldb-create-db dictionary_attack 

love:
	@echo "not war"

