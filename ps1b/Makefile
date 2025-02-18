CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST_LIBS = -lboost_unit_test_framework
AR = ar
ARFLAGS = rcs

all: PhotoMagic test PhotoMagic.a 

PhotoMagic: main.o PhotoMagic.o FibLFSR.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

test: test.o FibLFSR.o PhotoMagic.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS)

PhotoMagic.a: PhotoMagic.o FibLFSR.o
	$(AR) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o PhotoMagic test PhotoMagic.a

.PHONY: all clean
