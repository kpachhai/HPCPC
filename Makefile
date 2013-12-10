EXES = serial_brute_force
F = passlist/simplewords.txt
A = passlist/test.txt
B = dictionary_attack
C = 10

D = d-a-leveldb-create-db
E = d-a-leveldb

G = passlist/wordsforsimpletest.txt
GG = passlist/hashFileToTest.txt
J = passlist/wordsfortestLeveldb.txt
JJ = passlist/wordsfortestLeveldbGPU.txt
I = passlist/convertedHash.txt
II = passlist/convertedHashLeveldb.txt
K = passlist/convertedHashLeveldbGPU.txt

P = 1
H = passlist/hashFileToTest.txt
M = 4

GCC = g++

all: $(EXES)
	$(GCC) -Wall -O3 -o $@ $^

mpi_brute_force:
	mpic++ mpi_brute_force.cpp -o $@

run_mpi_brute:
	mpirun -np $(P) ./mpi_brute_force $(H) $(M)

dic_attack_basic:
	$(GCC) -O3 -o $(B) dictionary_attack.cpp
#	./dictionary_attack $(G) 16 $(GG) 16 $(I)

dic_attack_create_db:
	$(GCC) -O3 -o $(D) d-a-leveldb-create-db.cpp leveldb/libleveldb.a -lpthread -I leveldb/include

dic_attack_db_exec:
	$(GCC) -O3 -o $(E) d-a-leveldb.cpp leveldb/libleveldb.a -lpthread -I leveldb/include
#	./d-a-leveldb $(J) 394748 $(II)

dic_attack_db_exec_gpu:
	nvcc -O3 -o dic_attack_gpu d-a-leveldb-cuda.cu leveldb/libleveldb.a -lpthread -I leveldb/include
	./dic_attack_gpu $(JJ) 895 $(K)

convert:
	$(GCC) convert_md5_txt.cpp -o convert -lcrypto -lssl

makehashes:
	$(GCC) make_hashes_pass_files_for_test.cpp -o make_hashes -lcrypto -lssl
	
test:
	python performance.py $(A) $(B) $(C) $(P)

clean:
	rm -f $(EXES)
	rm -f mpi_brute_force d-a-leveldb d-a-leveldb-create-db dictionary_attack d-a-leveldb-mpi convert 

love:
	@echo "not war"

