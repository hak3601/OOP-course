# Variables for compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS =

# Platform-specific settings
ifeq ($(OS), Windows_NT)
    # Windows settings
    EXECUTABLE = main.exe
    RM = del /Q /F
else
    # macOS/Linux settings
    EXECUTABLE = main
    RM = rm -f
endif

# Directories
SRC_DIR = code
OBJ_DIR = obj

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	$(RM) $(EXECUTABLE)
	$(RM) $(OBJ_DIR)/*.o

# Phony targets
.PHONY: all clean
