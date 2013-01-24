#ifndef SERIALTALK_H
#define SERIALTALK_H

int openSerial(char* dev_path);
void closeSerial(int dev);
int sendData(unsigned char *data, int size, int dev);

#endif
