CC = gcc
SRC_DIR = ./functions
SRC_DIR_SQL = ./functions/sql
SRC_DIR_CPNT = ./functions/components
BIN_DIR = ./bin
LIB_DIR = ./lib
PY1 = -I/Library/Frameworks/Python.framework/Versions/3.11/include/python3.11
PY2 = -L/Library/Frameworks/Python.framework/Versions/3.11/lib
STAT = ./functions/components/py

# Liste des fichiers source
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES_UN = $(wildcard $(SRC_DIR_SQL)/*.c)
SRC_FILES_DEUX = $(wildcard $(SRC_DIR_CPNT)/*.c)
OBJ_FILES_1 = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))
OBJ_FILES_2 = $(patsubst $(SRC_DIR_SQL)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES_UN))
OBJ_FILES_3 = $(patsubst $(SRC_DIR_CPNT)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES_DEUX))

# execution du projet
all: $(BIN_DIR)/event run

# Fichier objet

$(BIN_DIR)/%.o: $(SRC_DIR_SQL)/%.c
	$(CC) -c $< -o $@ 

$(BIN_DIR)/%.o: $(SRC_DIR_CPNT)/%.c
	$(CC) -c $< -o $@ 

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@  $(PY1) $(PY2) -lpython3.11

# $(BIN_DIR)/%.o: $(STAT)/%.c
# 	$(CC) -c -o $@ $< $(PY1) $(PY1) -lpython3.11

# Librairie statique
$(LIB_DIR)/libevent.a: $(BIN_DIR)/*.o
	ar rcs $@ $^

# liaisin fichier objet et la librairie statique
$(BIN_DIR)/event: $(OBJ_FILES_1) $(OBJ_FILES_2) $(OBJ_FILES_3) $(LIB_DIR)/libevent.a
	$(CC) -c $^ -lsqlite3 -o $@ 

# Nottoyage
clean:
	rm -f $(BIN_DIR)/* $(LIB_DIR)/*

# Run the program
run:
	$(BIN_DIR)/event