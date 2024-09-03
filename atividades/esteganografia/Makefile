CC = gcc

CFLAGS = -Wall -O2

LIBS = -lpng -lz

TARGET = esteganografia

SRCS = esteganografia.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
