#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "commands.h"
void
readCommand(const char* pipeServer, const char *pipeClient)
{
  int fifo_s, fifo_c;
  char* buf;
  int command;
  fifo_s = open(pipeServer, O_RDWR);
  fifo_c = open(pipeClient, O_RDWR);

  if (fifo_s < 1){
    fprintf(stderr, "Error: cannot open server pipe\n");
    exit -1;
  }
  if (read(fifo_s, &command, sizeof(int)) == sizeof(int)){
    cmdnr = command;
    buf="OK";
    write(fifo_c,buf,5*sizeof(char));
  }
  close(fifo_s);
  close(fifo_c);
}


