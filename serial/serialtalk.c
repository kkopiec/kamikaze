/******************************************************************************
 * opening serial line (to arduino) for raw data transport
 ******************************************************************************/

#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serialtalk.h"
int fdsl;
struct termios tty, orig_tty;
/******************************************************************************
 * open serial line to the device dev and set it to raw interface
 * then return device descriptor
 */

int openSerial(char* dev_path)
{
  if((fdsl = open(dev_path, O_RDWR|O_NOCTTY|O_NDELAY)) == -1){
    fprintf(stderr, "cannoct open serial line %s\n",dev_path);
    exit(-1);
  }
  fcntl(fdsl, F_SETFL, 0);

  if ((tcgetattr(fdsl, &tty) < 0)){
    fprintf(stderr,"Cannot read port attributes!\n");
    close(fdsl);
    exit(-1);
  }
  
  orig_tty = tty;
  cfmakeraw(&tty);
  if((cfsetospeed (&tty, B115200)) ==-1){
    fprintf(stderr, "cannot set desired speed of the line\n");
    close(fdsl);
    exit(-1);
  }
  //tty.c_cflag &= ~PARENB;
  //tty.c_cflag &= ~CSTOPB;
  //tty.c_cflag &= ~CSIZE;
  //tty.c_cflag |= CS8;
  if (tcsetattr(fdsl, TCSAFLUSH, &tty) < 0){
    fprintf(stderr, "Cannot set raw terminal on %s\n",dev_path);
    close(fdsl);
    exit (-1);
  }
  sleep(1);
  return fdsl;
}

void closeSerial(int dev)
{
  if (tcsetattr(dev, TCSAFLUSH, &orig_tty) < 0){
    fprintf(stderr, "Cannot set back terminal on /dev/ttyACM0\n");
    close(fdsl);
    exit(-1);
  }
  close(dev);
}

int sendData(unsigned char *data, int size, int dev)
{
  int g = 0;
  int w = 0;
  unsigned char *test = data;
  while(g < size){
    g+=8;
    if ((w = write(dev, test, 8)) != 8){
      fprintf(stderr, "something wrong went with writting!\n");
      close(dev);
      exit (-1);
    }
    //else printf("Sending: %x %x\n", *test , *(test+1));
    test+=8;
    //sleep(2);
  }

}

/*
int main(int argc, char *argv[])
{
  if((fdsl = open("/dev/ttyACM0", O_RDWR|O_NOCTTY|O_NDELAY)) == -1){
    fprintf(stderr, "cannoct open serial line /dev/ttyACM0\n");
    exit(-1);
  }
  fcntl(fdsl, F_SETFL, 0);

  if ((tcgetattr(fdsl, &tty) < 0)){
    fprintf(stderr,"Cannot read port attributes!\n");
    close(fdsl);
    exit(-1);
  }
  
  orig_tty = tty;
  cfmakeraw(&tty);
  if((cfsetospeed (&tty, B9600)) ==-1){
    fprintf(stderr, "cannot set desired speed of the line\n");
    close(fdsl);
    exit(-1);
  }
  //tty.c_cflag &= ~PARENB;
  //tty.c_cflag &= ~CSTOPB;
  //tty.c_cflag &= ~CSIZE;
  //tty.c_cflag |= CS8;
  if (tcsetattr(fdsl, TCSAFLUSH, &tty) < 0){
    fprintf(stderr, "Cannot set raw terminal on /dev/ttyACM0\n");
    close(fdsl);
    exit (-1);
  }
  sleep(1);
  /***********************
   * raw terminal here
   ***********************/
/*
  unsigned char *test ;
  unsigned char data[] = {
    0xFF,0xFF,0xFF,0xFF,0,0,0,0,
    0xFF,0xFF,0xFF,0xFF,0,0,0,0,
    0,0,0,0,0,0,0,0};//,2,3,4,5,6,7,8,9,10,0,0,0,0,0,0};

    /*
    {1,2,4,8,
     16,32,64,128,
     128,64,32,16,
     8,4,2,1
    };
    */ 

/*
  test = data;
  int w;
  int g=0;
  while(g < 16){
    g+=8;
    if ((w = write(fdsl, test, 8)) != 8){
      fprintf(stderr, "something wrong went with writting!\n"); int
      close(fdsl);
      exit (-1);
    }
    else printf("Sending: %x %x\n", *test , *(test+1));
    test+=8;
    //sleep(2);
  }
  

  if (tcsetattr(fdsl, TCSAFLUSH, &orig_tty) < 0){
    fprintf(stderr, "Cannot set back terminal on /dev/ttyACM0\n");
    close(fdsl);
    exit(-1);
  }
  close(fdsl);

  return 0;
}
*/
