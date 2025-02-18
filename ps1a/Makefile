CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -lboost_unit_test_framework

# Object files
OBJS = FibLFSR.o

# Targets
all: PhotoMagic.a PhotoMagic.o test

PhotoMagic.a: $(OBJS)
	ar crs $@ /dev/null
	ar d $@ /dev/null
	ar r $@ $^

PhotoMagic.o:
	ar crs PhotoMagic /dev/null
	ar d PhotoMagic.a /dev/null
	objcopy --output-target=elf64-x86-64 PhotoMagic.a $@

fiblfsr.o: FibLFSR.cpp FibLFSR.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: test.o PhotoMagic.a
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test.o: test.cpp FibLFSR.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

lint:
	@echo "Linting all source files..."
	@$(CXX) $(CXXFLAGS) -fsyntax-only FibLFSR.cpp test.cpp

clean:
	rm -f *.o *.a test

.PHONY: all clean lint