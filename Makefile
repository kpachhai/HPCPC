EXES = brute_force
F = passlist/simplewords.txt
A = passlist/test.txt
B = dictionary_attack
C = 10

D = d-a-leveldb-create-db
E = d-a-leveldb

GCC = g++

all: $(EXES)
	$(GCC) -Wall -O3 -o $@ $^

mpi_brute_force:
	mpicc mpi_brute_force.cpp  -o $@

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

