# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -O2 -pedantic

# Targets
SRC = ps7.cpp
OBJ = $(SRC:.cpp=.o)
EXE = ps7

# Default target
all: $(EXE)

# Build the executable
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linting (optional, use a tool like clang-tidy if available)
lint:
	clang-tidy $(SRC)

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXE) *.rpt