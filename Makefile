# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -I./src

# All source files
SRC = $(shell find src -name "*.c")

# Object files
OBJ = $(SRC:.c=.o)

# Executable
TARGET = lsbImageSteganography.out

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile each .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(TARGET)