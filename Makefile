# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -I./src

# All source files
SRC = $(shell find src -name "*.c")

# Output executable
TARGET = lsbImageSteaganography.out

# Build and run target
run:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "Build complete -> $(TARGET)"

# Clean
clean:
	rm -f $(TARGET)
	@echo "Clean complete"