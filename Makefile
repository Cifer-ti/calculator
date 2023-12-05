# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wunused-parameter -g

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
MAIN_SRC = $(SRC_DIR)/calc.c
SCILIB_SRC = $(SRC_DIR)/scilib/scilib.c
STACK_SRC = $(SRC_DIR)/stack/stack.c
MATXLIB_SRC = $(SRC_DIR)/matxlib/matxlib.c
COMPLIB_SRC = $(SRC_DIR)/complib/complib.c

# Object files
MAIN_OBJ = $(OBJ_DIR)/calc.o
SCILIB_OBJ = $(OBJ_DIR)/scilib.o
STACK_OBJ = $(OBJ_DIR)/stack.o
MATXLIB_OBJ = $(OBJ_DIR)/matxlib.o
COMPLIB_OBJ = $(OBJ_DIR)/complib.o

# Final executable
TARGET = calc

# Default target
all: $(TARGET)

# Compile the main program
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the scilib module
$(SCILIB_OBJ): $(SCILIB_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the stack module
$(STACK_OBJ): $(STACK_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the matxlib module
$(MATXLIB_OBJ): $(MATXLIB_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the complib module
$(COMPLIB_OBJ): $(COMPLIB_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the objects and create the final executable
$(TARGET): $(MAIN_OBJ) $(SCILIB_OBJ) $(STACK_OBJ) $(MATXLIB_OBJ) $(COMPLIB_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Clean the build directory
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)