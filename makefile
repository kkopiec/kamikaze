$CC= gcc
$JACKFLAGS= `pkg-config --cflags --libs jack`

grabber: main.c grab.o
	$(CC) -o grabber $(JACKFLAGS) main.c grab.c

grab.o:	grab.h grab.c
	$(CC) -c $(JACKFLAGS) grab.c
