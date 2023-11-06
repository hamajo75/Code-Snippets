CC = gcc
CFLAGS = -Wall -Wextra -c

# Source and object file directories
SRC_DIR = .
BUILD_DIR = build

# List of source files
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Generate the list of object files
C_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))

# Name of the static library
LIBRARY = libmathlib.a

# Default target
all: $(LIBRARY)

# Build the static library
$(LIBRARY): $(C_OBJECTS)
	ar rcs $@ $^

# Compile C source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Create the build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Clean up
clean:
	rm -f $(C_OBJECTS) $(LIBRARY)
