CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -pedantic -g
LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics

all: EDistance test EDistance.a

EDistance: main.o EDistance.o
	$(CXX) $(CXXFLAGS) -o EDistance main.o EDistance.o $(LDFLAGS)

test: test.o EDistance.o
	$(CXX) $(CXXFLAGS) -o test test.o EDistance.o $(LDFLAGS) -lboost_unit_test_framework

# Target to build the static library
EDistance.a: EDistance.o
	ar rcs EDistance.a EDistance.o

EDistance.o: EDistance.cpp EDistance.hpp
	$(CXX) $(CXXFLAGS) -c EDistance.cpp

main.o: main.cpp EDistance.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp EDistance.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

lint:
	cppcheck --enable=all --std=c++11 .

clean:
	rm -f *.o EDistance test EDistance.a