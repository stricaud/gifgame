CC=gcc
CFLAGS=-ggdb
LIBS=-lgif
RM=rm -f

all: randomgif

randomgif: randomgif.c
	$(CC) $(CFLAGS) $(LIBS) $< -o $@

clean:
	$(RM) randomgif
	$(RM) out.gif
	$(RM) *~
