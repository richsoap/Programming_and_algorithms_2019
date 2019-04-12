cxx = g++
tail = -std=c++11 -g

all: 
	$(cxx) main.cpp bignumber.cpp stopwatch.hpp $(tail) -o test
	$(cxx) generatenumbers.cpp numbergenerator.cpp $(tail) -o generate

