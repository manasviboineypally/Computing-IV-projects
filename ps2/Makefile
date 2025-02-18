CXX = g++
CXXFLAGS = -Wall -std=c++17
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC = main.cpp penta.cpp
OBJ = main.o penta.o
OUT = Penta
$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUT) $(SFML_LIBS)

main.o: main.cpp penta.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

penta.o: penta.cpp penta.hpp
	$(CXX) $(CXXFLAGS) -c penta.cpp

clean:
	rm -f $(OBJ) $(OUT)
