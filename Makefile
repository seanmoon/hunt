all:	huntc huntd

huntc:
	cc huntc.c -lcurses -o bin/huntc

huntd:
	cc huntd.c -o bin/huntd

clean:
	rm bin/*
