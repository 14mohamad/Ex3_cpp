# Makefile for Catan Game

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable names
EXEC = catan
TEST_EXEC = runtests

# Targets
all: $(BIN_DIR)/$(EXEC) $(BIN_DIR)/$(TEST_EXEC)

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile game executable
$(BIN_DIR)/$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile test executable
$(BIN_DIR)/$(TEST_EXEC): $(OBJS) $(OBJ_DIR)/TestPlayer.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game
run: $(BIN_DIR)/$(EXEC)
	./$(BIN_DIR)/$(EXEC)

# Run the tests
test: $(BIN_DIR)/$(TEST_EXEC)
	./$(BIN_DIR)/$(TEST_EXEC)

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run test clean
