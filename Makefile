########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = program
EXT = .cpp
SRCDIR = code
OBJDIR = obj

############## Do not change anything from here downwards! #############

# Sources, objects, and dependencies
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

# Platform-specific commands
OS := $(shell uname)
ifeq ($(OS), Windows_NT)
    RM = del
    MKDIR = mkdir
    EXE = .exe
else
    RM = rm -f
    MKDIR = mkdir -p
    EXE =
endif

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Ensure the obj directory exists
$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@$(EXE) $^ $(LDFLAGS)

# Creates the dependency rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CC) $(CXXFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) > $@

# Includes all dependency files
-include $(DEP)

# Compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) | $(OBJDIR)
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Cleaning rules
.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP) $(APPNAME)$(EXE)

.PHONY: cleandep
cleandep:
	$(RM) $(DEP)
