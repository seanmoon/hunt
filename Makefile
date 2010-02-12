BINS = bin/huntc bin/huntd

all:	$(BINS)


bin/huntc: LDFLAGS=-lcurses
bin/huntc: maze.o

bin objs:
	mkdir $@

bin/%: objs/%.o | bin
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

objs/%.o: %.c | objs
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	-rm $(BINS)
	-rm objs/*
