# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2
SRC_DIR = code
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = main

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compile source files to object files
code/%.o: code/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the compiled program
run: $(TARGET)
	./$(TARGET)

# Clean up object files and the executable
clean:
	rm -f $(TARGET) $(OBJ)
