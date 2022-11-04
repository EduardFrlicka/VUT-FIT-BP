#AUTHOR : Eduard Frlička


# =========================================================================
# Names and Directories

# Flags for compiling
CFLAGS:=-std=c++17 -Wall -Wextra -pedantic -ggdb3# -Wno-unused-parameter

LFLAGS:=

# Name of target binary file
BINARY_PATH:=../../bin/translate

# Name / Path to folder, where .o files will be stored
OBJ:=../../obj

# Name / Path to folder, where .dep files will be stored
DEP:=$(OBJ)

# Name / Path to folder, where source files are (.h .c .cpp ...)
SRC:=.

# Compiler
CXX:=g++

# Suffix of files to compile (E.x.: c, cpp, c++)
SUFFIX:=cpp

# rm command
RM:=rm 


# =========================================================================
# initializing global variables

SRC_DIRECTORIES=$(shell find $(SRC) -type d)

vpath %.$(SUFFIX) $(SRC_DIRECTORIES)
vpath %.h $(SRC_DIRECTORIES)

# Adding -I 
INCLUDE:=$(foreach DIR, $(SRC_DIRECTORIES),-I $(DIR))

SOURCES  := $(foreach DIR,$(SRC_DIRECTORIES),$(notdir $(wildcard $(DIR)/*.$(SUFFIX))))
OBJECTS  := $(patsubst %.$(SUFFIX),$(OBJ)/%.o,$(SOURCES))

ifeq ($(SOURCES),)
$(error No source files found in directory "$(SRC)")
endif

# =========================================================================
# Targets
.PHONY:  all run clean cleanall source help
.PRECIOUS: $(DEP)/%.dep


# =========================================================================
# Rules
all: $(BINARY_PATH) 

run: $(BINARY_PATH) 
	./$(BINARY_PATH)

help: $(BINARY_PATH)
	./$(BINARY_PATH) -h

$(BINARY_PATH) : $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LFLAGS) $(INCLUDE)

$(OBJ)/%.o: %.$(SUFFIX) $(DEP)/%.dep
	@mkdir -p $(@D)
	$(CXX) $< -c -o $@ $(CFLAGS) $(INCLUDE)

$(DEP)/%.dep: %.$(SUFFIX)
	@mkdir -p $(@D)
	@$(CXX) -MT "$(patsubst $(DEP)/%.dep,$(OBJ)/%.o,$@) $@" -MM $< -o $@ $(INCLUDE)

source:
	@echo "Sources: " $(SOURCES)
	@echo "Objects: " $(OBJECTS)
	@echo "Source_Folders: " $(SRC_DIRECTORIES)


# =========================================================================
# Cleaning rules
clean:
	$(RM) -f $(OBJ)/*.o $(DEP)/*.dep

cleanall: clean
	$(RM) -f $(BINARY_PATH)
	$(RM) -df $(DEP) $(OBJ)

-include $(wildcard $(DEP)/*.dep)