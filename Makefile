BINS = bin/huntc 

all:	$(BINS)


bin/huntc: LDFLAGS=-lcurses
bin/huntc: objs/maze.o

bin objs:
	mkdir $@

bin/%: objs/%.o | bin
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

objs/%.o: %.c | objs
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	-rm $(BINS)
	-rm objs/*
