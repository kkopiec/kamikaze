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

int fdsl;
struct termios tty, orig_tty;
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
  //cfmakeraw(&tty);
  if((cfsetospeed (&tty, B9600)) ==-1){
    fprintf(stderr, "cannot set desired speed of the line\n");
    close(fdsl);
    exit(-1);
  }
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  if (tcsetattr(fdsl, TCSAFLUSH, &tty) < 0){
    fprintf(stderr, "Cannot set raw terminal on /dev/ttyACM0\n");
    close(fdsl);
    exit (-1);
  }
  sleep(1);
  /***********************
   * raw terminal here
   ***********************/
  unsigned char *test ;
  unsigned char data[] = {1,2,4,8,
			  16,32,64,128,
			  128,64,32,16,
			  8,4,2,1
  }; 
  test = data;
  int w;
  int g=0;
  while(g < 16){
    g+=8;
    if ((w = write(fdsl, &test, 8)) != 8){
      fprintf(stderr, "something wrong went with writting!\n");
      close(fdsl);
      exit (-1);
    }
    test+=8;
  }
  

  if (tcsetattr(fdsl, TCSAFLUSH, &orig_tty) < 0){
    fprintf(stderr, "Cannot set back terminal on /dev/ttyACM0\n");
    close(fdsl);
    exit(-1);
  }
  close(fdsl);

  return 0;
}
