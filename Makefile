# CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`-lm 
OUTFILE=main

main: main.c
	$(CC) $(CFLAGS) -o $(OUTFILE) main.c $(LIBS)

run: $(OUTFILE)
	./$(OUTFILE)
