# Nome do executável
EXEC = main

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Coleta todos os arquivos .c na pasta atual
SRCS = $(wildcard *.c)
# Converte cada .c em um .o
OBJS = $(SRCS:.c=.o)

# Regra principal para compilar o programa
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regra para compilar cada arquivo .c em um .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos objetos e do executável
clean:
	rm -f $(OBJS) $(EXEC)

# Limpeza apenas dos arquivos objetos
clean_obj:
	rm -f $(OBJS)

# Regra padrão para rodar o programa
run: $(EXEC)
	./$(EXEC) in.txt
