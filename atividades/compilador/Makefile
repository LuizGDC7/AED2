# Nome do executável
EXEC = main

# Compilador e flags de compilação
CC = gcc
CFLAGS =

# Diretórios
SRC_DIR = implementation
INC_DIR = header
OBJ_DIR = obj

# Arquivo principal
MAIN = main.c

# Busca todos os arquivos .c dentro do diretório src
SRC = $(wildcard $(SRC_DIR)/*.c)

# Converte todos os .c em .o, armazenando-os no diretório obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regra padrão para compilar o executável
$(EXEC): $(OBJ_DIR) $(OBJ) $(MAIN)
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN) $(OBJ)

# Regra para compilar os arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o diretório de objetos, se necessário
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza dos arquivos compilados
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

# Limpeza completa
cleanall: clean
	clear
	rm -rf $(OBJ_DIR)

run: 
	./main in.txt