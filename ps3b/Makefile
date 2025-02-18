CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -pedantic -g
LDFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

SRCS = main.cpp Universe.cpp CelestialBody.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = NBody

all: $(EXECUTABLE) NBody.a

NBody.a: Universe.o CelestialBody.o
	ar rcs $@ $^

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE) NBody.a

.PHONY: all clean