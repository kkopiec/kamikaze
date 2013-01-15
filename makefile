$CC= gcc
$JACKFLAGS= -ljack -lfttw3 -lm

grabber: main.c grab.o
	$(CC) -o grabber $(JACKFLAGS) main.c grab.c

grab.o:	grab.h grab.c
	$(CC) -c $(JACKFLAGS) grab.c
