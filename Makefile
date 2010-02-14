BINS = bin/huntc 

all:	$(BINS)

CFLAGS = -Wall -g

PKG_LIBS = glib-2.0

bin/huntc: LDFLAGS+=-lcurses -lev `pkg-config --libs $(PKG_LIBS)`
bin/huntc: CFLAGS+=`pkg-config --cflags $(PKG_LIBS)`
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
