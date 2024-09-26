# Variáveis do Makefile
CC = gcc                  # Compilador
CFLAGS = -Iinclude -Wall -lm # Flags de compilação (-I para incluir cabeçalhos)
LDFLAGS = -Llib  # Flags de linkagem (-L para localizar bibliotecas, -l para a biblioteca)
OBJ = src/main.o src/calculator.o src/linked_list.o src/dinamic_queue_and_stack.o # Objetos que serão criados a partir dos arquivos .c
TARGET = calculadora      # Nome do executável final

# Regra principal (padrão). O alvo será o nome do programa.
all: $(TARGET)

# Regra para compilar o programa final
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Regra genérica para compilar os arquivos .c em .o (objetos)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos temporários (objetos e executáveis)
clean:
	rm -f $(OBJ) $(TARGET)

# Rodar o programa (opcional)
run: $(TARGET)
	./$(TARGET)

