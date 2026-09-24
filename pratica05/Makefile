CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o coloracao.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c coloracao.h
	$(CC) $(CFLAGS) -c main.c

coloracao.o: coloracao.c coloracao.h
	$(CC) $(CFLAGS) -c coloracao.c

clean:
	rm -f $(OBJ) main main.exe
