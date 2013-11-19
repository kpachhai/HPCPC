EXES = brute_force

all: $(EXES)
	gcc -Wall -O3 -o $@ $^ $(LIBS)

clean:
	rm -f $(EXES)

love:
	@echo "not war"
