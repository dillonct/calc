CC:=gcc
CFLAGS:=-g
BIN_NAME:=calc
SRC_DIR:=src
INCLUDE_DIR:=include
BIN_DIR:=bin

# Collect all .c files in SRC_DIR
SOURCES:=$(wildcard $(SRC_DIR)/*.c)
# Generate .o file names from .c file names
OBJECTS:=$(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

default: $(BIN_DIR)/$(BIN_NAME)
	$(BIN_DIR)/$(BIN_NAME)

# Link all object files to create the final binary
$(BIN_DIR)/$(BIN_NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lm

# Compile each .c file to an .o file
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BIN_DIR)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BIN_DIR)

.PHONY: clean

