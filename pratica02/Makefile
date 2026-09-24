CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o busca_largura.o busca_profundidade.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c busca_largura.h busca_profundidade.h
	$(CC) $(CFLAGS) -c main.c

busca_largura.o: busca_largura.c busca_largura.h
	$(CC) $(CFLAGS) -c busca_largura.c

busca_profundidade.o: busca_profundidade.c busca_profundidade.h busca_largura.h
	$(CC) $(CFLAGS) -c busca_profundidade.c

clean:
	rm -f $(OBJ) main main.exe
