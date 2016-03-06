OPTIMIZE=-O2
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11
DEPS = addtest.h
OBJ = main.o addtest.h
SOURCES = Makefile addtest.c addtest.h main.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

addtest: $(OBJ)
	gcc $(CFLAGS) -o $@ $^


check:
	

dist: lab1DP-GarimaLunawatBreannaNery.tar.gz
lab4.1-GarimaLunawatBreannaNery.tar.gz: $(SOURCES)
	mkdir lab4.1-GarimaLunawatBreannaNery
	cp $(SOURCES) lab4.1-GarimaLunawatBreannaNery
	tar -czf $@ lab4.1-GarimaLunawatBreannaNery
	rm -r lab4.1-GarimaLunawatBreannaNery

clean:
	rm -f *.o *.so *.so.* addtest lab4.1-GarimaLunawatBreannaNery.tar.gz lab4.1-GarimaLunawatBreannaNery


