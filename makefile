CC= gcc
JACKFLAGS= -ljack -lfftw3 -lm
all: grabber IPC
<<<<<<< HEAD
grabber: main.c grab.o ffts.o windows.o image.o animation.o commands.o compressor.o global.h 
	$(CC) -o grabber main.c grab.o ffts.o windows.o image.o animation.o commands.o compressor.o $(JACKFLAGS)
=======
grabber: main.c grab.o ffts.o windows.o image.o animation.o commands.o Connection.o global.h 
	$(CC) -o grabber main.c grab.o ffts.o windows.o image.o animation.o commands.o Connection.o $(JACKFLAGS)
>>>>>>> 4d0f1169d05f40cc9528c37fc3a6b4b76a6f9678

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

<<<<<<< HEAD
compressor.o: compressor.c compressor.h
	$(CC) -c compressor.c $(JACKFLAGS)
=======
Connection.o: Connection.c Connection.h
	$(CC) -c Connection.c $(JACKFLAGS)

>>>>>>> 4d0f1169d05f40cc9528c37fc3a6b4b76a6f9678
IPC: IPC.c
	$(CC) -o IPC IPC.c

