CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o conectividade.o planaridade.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c conectividade.h planaridade.h
	$(CC) $(CFLAGS) -c main.c

conectividade.o: conectividade.c conectividade.h
	$(CC) $(CFLAGS) -c conectividade.c

planaridade.o: planaridade.c planaridade.h conectividade.h
	$(CC) $(CFLAGS) -c planaridade.c

clean:
	rm -f $(OBJ) main main.exe
