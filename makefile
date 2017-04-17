CC=gcc
FILENAME=test.c
BINDIR=bin
EXENAME=test

all:
	mkdir -p $(BINDIR)
	$(CC) $(FILENAME) pfr/pfr.c -o $(BINDIR)/$(EXENAME) 

clean:
	rm -rf $(BINDIR)

