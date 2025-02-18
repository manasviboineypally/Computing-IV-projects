CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -pedantic -g
LDFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

SRCS = main.cpp Universe.cpp CelestialBody.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = NBody
TEST_SRCS = test.cpp Universe.cpp CelestialBody.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXECUTABLE = test

all: $(EXECUTABLE) $(TEST_EXECUTABLE) NBody.a

NBody.a: Universe.o CelestialBody.o
	ar rcs $@ $^

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(TEST_EXECUTABLE): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(EXECUTABLE) $(TEST_EXECUTABLE) NBody.a

.PHONY: all clean