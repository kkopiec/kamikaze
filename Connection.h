#ifndef CONNECTION_H
#define CONNECTION_H

int sendToArduino(unsigned char* buffer);

int initiateSerialLine();

int closeSerialLine();

#endif
