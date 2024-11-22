# Nome do executável final
TARGET = main

# Diretórios
HEADERS_DIR = header
SRC_DIR = implementation
BUILD_DIR = build

# Busca todos os arquivos .c no diretório de implementação
SOURCES = $(wildcard $(SRC_DIR)/*.c)
# Converte os arquivos .c em arquivos .o (objetos)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
# Inclui o arquivo main.c diretamente
MAIN_OBJECT = $(BUILD_DIR)/main.o

# Compilador e flags
CC = gcc
CFLAGS = #-I$(HEADERS_DIR) -Wall -Wextra -O2

# Regra padrão (primeiro alvo)
all: $(BUILD_DIR) $(TARGET)

# Regra para criar o executável final
$(TARGET): $(OBJECTS) $(MAIN_OBJECT)
	$(CC) $(OBJECTS) $(MAIN_OBJECT) -o $(TARGET)

# Regra para compilar arquivos .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar main.c em main.o
$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar o diretório de build, se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Regra para limpar e recompilar
rebuild: clean all

run: 
	./main < in.txt
