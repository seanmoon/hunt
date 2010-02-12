BINS = bin/huntc 

all:	$(BINS)

CFLAGS = -Wall -g


bin/huntc: LDFLAGS=-lcurses
bin/huntc: objs/maze.o objs/huntc.o

bin objs:
	mkdir $@

bin/%: | bin
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


objs/%.o: %.c | objs
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	-rm $(BINS)
	-rm objs/*
