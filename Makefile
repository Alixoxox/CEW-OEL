CC = gcc
CFLAGS = -Iinclude -I/usr/include/cjson -I/usr/include/curl -Wall -Werror # Added include path for cJSON and libcurl 
SRC_DIR = src
OBJ_DIR = obj
# Removed the BIN_DIR variable
TARGET = output # Changed the target to output in the root directory

# List all source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
# Convert source file names to object file names
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Default rule
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lcurl -lcjson # Output file in the root directory

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

