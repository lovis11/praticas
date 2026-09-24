CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o grafo_matriz.o grafo_lista.o

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c grafo_matriz.h grafo_lista.h
	$(CC) $(CFLAGS) -c main.c

grafo_matriz.o: grafo_matriz.c grafo_matriz.h
	$(CC) $(CFLAGS) -c grafo_matriz.c

grafo_lista.o: grafo_lista.c grafo_lista.h
	$(CC) $(CFLAGS) -c grafo_lista.c

clean:
	rm -f $(OBJ) main main.exe
