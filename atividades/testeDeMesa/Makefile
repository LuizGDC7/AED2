TARGET = main

# Lista de arquivos .c
SRCS = main.c bintree.c

# Lista de arquivos .o gerados (um .o para cada .c)
OBJS = $(SRCS:.c=.o)

# Flags do compilador
CFLAGS = -Wall -g

# Regra padrão: compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar os arquivos objeto (.o) e o executável
clean:
	rm -f $(OBJS) $(TARGET)

# Regra "phony" para evitar conflitos com arquivos reais
.PHONY: clean

make run:
	./main