OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11
DEPS = parser.h
OBJ = main.o parser.o
SOURCES = Makefile addtest.c main.c parser.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

parser: $(OBJ)
	gcc $(CFLAGS) -o $@ $^


check:
	

dist: lab4.1-GarimaLunawatBreannaNery.tar.gz
lab4.1-GarimaLunawatBreannaNery.tar.gz: $(SOURCES)
	mkdir lab4.1-GarimaLunawatBreannaNery
	cp $(SOURCES) lab4.1-GarimaLunawatBreannaNery
	tar -czf $@ lab4.1-GarimaLunawatBreannaNery
	rm -r lab4.1-GarimaLunawatBreannaNery

clean:
	rm -f *.o *.so *.so.* addtest lab4.1-GarimaLunawatBreannaNery.tar.gz lab4.1-GarimaLunawatBreannaNery


