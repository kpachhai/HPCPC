EXES = brute_force
F = passlist/simplewords.txt

all: $(EXES)
	mpicc -Wall -O3 -o $@ $^ $(LIBS)
	g++ -Wall convert_md5_txt.cpp -o convert_md5_txt -lcrypto -lssl

convert:
	./convert_md5_txt $(F)
clean:
	rm -f $(EXES)
	rm -rf convert_md5_txt

love:
	@echo "not war"

