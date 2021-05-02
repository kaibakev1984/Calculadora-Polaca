CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --show-reachable=yes --track-origins=yes
EXEC = pruebas
OBJFILE = calculadora_polaca.o 
TEXTFILE = oper.txt

%.0: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJFILE)
	$(CC) $(CFLAGS) $(OBJFILE) -o $(EXEC)

all: $(EXEC)

run: all
	./$(EXEC) < $(TEXTFILE)

clear: $(EXEC) $(OBJFILE)
	rm -f $(EXEC) *.o

valgrind: all
	valgrind $(VFLAGS) ./$(EXEC) < $(TEXTFILE)
