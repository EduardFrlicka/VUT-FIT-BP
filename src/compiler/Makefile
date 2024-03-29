#AUTHOR : Eduard Frlička


# =========================================================================
# Names and Directories

ROOT:=../..

# Name of target binary file
BINARY_PATH=$(ROOT)/bin/compiler

# Name / Path to folder, where source files are (.h .c .cpp ...)
SRC=.

# Name / Path to folder, where .o files will be stored
OBJ=$(ROOT)/obj/compiler

# Name / Path to folder, where .dep files will be stored
DEP=$(ROOT)/dep/compiler


# =========================================================================
# Commands and Flags

# Flags for compiling
CXXFLAGS:=-std=c++20 -Wall -Wextra -pedantic -ggdb3 -DDEBUG_PRINT

LFLAGS:=

# =========================================================================
# initializing global variables

SRC_DIRECTORIES=$(shell find $(SRC) -type d)
INCLUDE:=$(addprefix -I , $(SRC_DIRECTORIES))

SRCS  	:= $(shell find $(SRC) -type f -name '*.cc' -or -name '*.cpp')
OBJS  	:= $(SRCS:$(SRC)/%=$(OBJ)/%.o)
DEPS	:= $(SRCS:$(SRC)/%=$(DEP)/%.dep)


vpath %.cc $(SRC)
vpath %.cpp $(SRC)
vpath %.h $(SRC_DIRECTORIES)


ifeq ($(SRCS),)
$(error No source files found in directory "$(SRC)")
endif


# =========================================================================
# Targets
.PHONY:  all run clean cleanall source


# =========================================================================
# Rules
all: $(BINARY_PATH) 

run: $(BINARY_PATH) 
	./$(BINARY_PATH)

# Linking all objects
$(BINARY_PATH): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LFLAGS) $(INCLUDE)

# Compiling object
$(OBJ)/%.o: %
	@mkdir -p $(@D)
	$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)

# creating dep file
$(DEP)/%.dep: %
	@mkdir -p $(@D)
	@$(CXX) -MT "$(@:$(DEP)/%.dep=$(OBJ)/%.o) $@" -MM $< -o $@ $(INCLUDE)


source:
	@echo "SRCS: " $(SRCS)
	@echo "OBJS: " $(OBJS)
	@echo "DEPS: " $(DEPS)
	@echo "Source Folders: " $(SRC_DIRECTORIES)


# =========================================================================
# Cleaning rules
clean:
	$(RM) -f $(OBJS) $(DEPS)
# removing empty directories for objects and dependency files
	@test -d $(DEP) && find $(DEP) -empty -type d -delete || true
	@test -d $(DEP) && echo "Directory $(DEP) is not empty" || true
	@test -d $(OBJ) && find $(OBJ) -empty -type d -delete || true
	@test -d $(OBJ) && echo "Directory $(OBJ) is not empty" || true


cleanall: clean
	$(RM) -f $(BINARY_PATH)

-include $(DEPS)
