CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Executable name
EXEC = Sokoban

# Source files
SOURCES = main.cpp Sokoban.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = Sokoban.hpp

# Default target
all: $(EXEC) Sokoban.a

# Linking the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(SFML_LIBS)

# Compiling source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creating static library
Sokoban.a: Sokoban.o
	ar rcs $@ $^

# Linting
lint:
	cpplint --filter=-legal/copyright $(SOURCES) $(HEADERS)

# Cleaning up
clean:
	rm -f $(EXEC) $(OBJECTS) Sokoban.a

.PHONY: all lint clean