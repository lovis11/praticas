CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o dag.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c dag.h
	$(CC) $(CFLAGS) -c main.c

dag.o: dag.c dag.h
	$(CC) $(CFLAGS) -c dag.c

clean:
	rm -f $(OBJ) main main.exe
