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
DEPDIR = others

############## Do not change anything from here downwards! #############

# Sources, objects, and dependencies
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(SRC:$(SRCDIR)/%$(EXT)=$(DEPDIR)/%.d)

# UNIX-based OS variables & settings
RM = rm -f
MKDIR = mkdir -p

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Ensure the obj and dep directories exist
$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

$(DEPDIR):
	@$(MKDIR) $(DEPDIR)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependency rules
$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT) | $(DEPDIR)
	@$(CC) $(CXXFLAGS) $< -MM -MT $(OBJDIR)/$*.o > $@

# Includes all dependency files
-include $(DEP)

# Compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) | $(OBJDIR)
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Cleaning rules
.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP) $(APPNAME)

.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

# Run the program with "data" argument
.PHONY: run
run: $(APPNAME)
	./$(APPNAME) data