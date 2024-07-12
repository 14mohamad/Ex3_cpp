# Makefile for Catan Game

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Source files and object files
Board.o: Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp -o Board.o

DevelopmentCard.o: DevelopmentCard.cpp
	$(CXX) $(CXXFLAGS) -c DevelopmentCard.cpp -o DevelopmentCard.o

catan.o: catan.cpp
	$(CXX) $(CXXFLAGS) -c catan.cpp -o catan.o

player.o: player.cpp
	$(CXX) $(CXXFLAGS) -c player.cpp -o player.o

test_main.o: test_main.cpp
	$(CXX) $(CXXFLAGS) -c test_main.cpp -o test_main.o

# Executable names
catan: Board.o DevelopmentCard.o catan.o player.o
	$(CXX) $(CXXFLAGS) Board.o DevelopmentCard.o catan.o player.o -o catan

runtests: Board.o DevelopmentCard.o player.o test_main.o
	$(CXX) $(CXXFLAGS) Board.o DevelopmentCard.o player.o test_main.o -o runtests

# Targets
all: catan

# Run the game
run: catan
	./catan

# Run the tests
test: runtests
	./runtests

# Clean up generated files
clean:
	rm -f Board.o DevelopmentCard.o catan.o player.o test_main.o catan runtests

.PHONY: all run test clean
