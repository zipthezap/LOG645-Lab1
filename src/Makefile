CXX := g++
CXXOPT := -O3 -std=c++17 -g -Wall
LDFLAGS = -ldl

all: run test_verif

run: run.o verification.o
	$(CXX) -o $@ $^ $(LDFLAGS)

test_verif: test_verif.o verification.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXOPT)

clean:
	rm -Rf run test_verif *.o

.PHONY: clean
