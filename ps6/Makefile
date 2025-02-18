CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror
TEST_LIBS = -lboost_unit_test_framework

all: TextWriter test TextWriter.a

TextWriter: TextWriter.o RandWriter.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TextWriter.a: RandWriter.o
	ar rcs $@ $^

test: test.o RandWriter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

lint:
	cpplint *.cpp *.hpp

clean:
	rm -f *.o TextWriter TextWriter.a test

.PHONY: all lint clean