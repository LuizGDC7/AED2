# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR)
LIBS = -lm

# Diretórios
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

# Lista de fontes e objetos
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/calculadora

# Regra padrão
all: $(EXECUTABLE)

# Regra para linkar o executável
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)

# Regra para compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criação de diretórios se não existirem
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Alvo clean
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Dependências (opcional, mas recomendado)
-include $(OBJECTS:.o=.d)

# Regra para gerar dependências
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

run:
	./bin/calculadora < entrada.txt > saida.txt