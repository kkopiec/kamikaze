CC= gcc
JACKFLAGS= -ljack -lfftw3 -lm
all: grabber IPC
grabber: main.c grab.o ffts.o windows.o image.o animation.o commands.o compressor.o global.h 
	$(CC) -o grabber main.c grab.o ffts.o windows.o image.o animation.o commands.o compressor.o $(JACKFLAGS)

grab.o:	grab.h grab.c global.h
	$(CC) -c grab.c  $(JACKFLAGS)

ffts.o: ffts.h ffts.c global.h windows.o 
	$(CC) -c ffts.c windows.o  $(JACKFLAGS)

windows.o: windows.c windows.h global.h
	$(CC) -c windows.c $(JACKFLAGS)

image.o: image.h image.c
	$(CC) -c image.c $(JACKFLAGS)

animation.o: animation.c animation.h
	$(CC) -c animation.c $(JACKFLAGS)	

commands.o: commands.c commands.h
	$(CC) -c commands.c $(JACKFLAGS)

compressor.o: compressor.c compressor.h
	$(CC) -c compressor.c $(JACKFLAGS)
IPC: IPC.c
	$(CC) -o IPC IPC.c