cxx = g++
tail = -std=c++11 -g

all: 
	$(cxx) main.cpp bignumber.cpp stopwatch.hpp $(tail) -o test

