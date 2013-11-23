EXES = brute_force
F = passlist/simplewords.txt
A = passlist/test.txt
B = dictionary_attack
C = 10

all: $(EXES)
	g++ -Wall -O3 -o $@ $^

test:
	python performance.py $(A) $(B) $(C)

clean:
	rm -f $(EXES)

love:
	@echo "not war"

