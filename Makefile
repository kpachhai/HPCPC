EXES = brute_force

all: $(EXES)
	mpicc -Wall -O3 -o $@ $^ $(LIBS)

clean:
	rm -f $(EXES)

love:
	@echo "not war"
