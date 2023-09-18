CXX := g++
CXXOPT := -O3 -g -fPIC -I..

all: libtp1.so

libtp1.so: solution.o
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXOPT)

clean:
	rm -Rf libtp1.so *.o

.PHONY: clean
