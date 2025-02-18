CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -pedantic -g
SFML_LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
BOOST_LIBS = -lboost_unit_test_framework

SRCS = Sokoban.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

HDRS = Sokoban.hpp

all: Sokoban Sokoban.a test

Sokoban: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

Sokoban.a: Sokoban.o
	ar rcs $@ $^

test: test.o Sokoban.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

lint:
	cpplint --filter=-legal/copyright *.cpp *.hpp

clean:
	rm -f *.o Sokoban Sokoban.a test

.PHONY: all lint clean test