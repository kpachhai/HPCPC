EXES = brute_force
F = passlist/simplewords.txt

all: $(EXES)
	g++ -Wall -O3 -o $@ $^

convert:

clean:
	rm -f $(EXES)

love:
	@echo "not war"

