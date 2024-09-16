TARGET = investimentos
CC = gcc
CFLAGS = -Wall
SRCS = main.c getDados.c gerenciarInv.c atualizarInv.c mostrarDados.c
LIBS = -lm

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET).out $(SRCS) $(LIBS)

clean:
	rm -f *.o investimentos.out
