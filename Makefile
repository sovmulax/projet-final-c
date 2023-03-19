CC = gcc
SRC_DIR = ./functions
SRC_DIR_SQL = ./functions/sql
SRC_DIR_CPNT = ./functions/components
BIN_DIR = ./bin
LIB_DIR = ./lib

# Liste des fichiers source
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES = $(wildcard $(SRC_DIR_SQL)/*.c)
SRC_FILES = $(wildcard $(SRC_DIR_CPNT)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))
OBJ_FILES = $(patsubst $(SRC_DIR_SQL)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))
OBJ_FILES = $(patsubst $(SRC_DIR_CPNT)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))

# execution du projet
all: $(BIN_DIR)/event run

# liaisin fichier objet et la librairie statique
$(BIN_DIR)/event: $(OBJ_FILES) $(LIB_DIR)/libevent.a
	$(CC) -o $@ $^ -lsqlite3

# Fichier objet
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $<

$(BIN_DIR)/%.o: $(SRC_DIR_SQL)/%.c
	$(CC) -c -o $@ $<

$(BIN_DIR)/%.o: $(SRC_DIR_CPNT)/%.c
	$(CC) -c -o $@ $<

# Librairie statique
$(LIB_DIR)/libevent.a: 
	ar rcs $@ $^

# Nottoyage
clean:
	rm -f $(BIN_DIR)/* $(LIB_DIR)/*

# Run the program
run:
	$(BIN_DIR)/event