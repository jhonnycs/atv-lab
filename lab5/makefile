TARGET = investimentos
CC = gcc
CFLAGS = -Wall
SRCS = main.c getDados.c gerenciarInv.c calcInv.c
LIBS = -lm

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f *.o investimentos