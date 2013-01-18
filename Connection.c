#include <stdio.h>    
#include <stdlib.h> 
#include <stdint.h>   
#include <string.h>   
#include <unistd.h>   
#include <fcntl.h>    
#include <errno.h>    
#include <termios.h>  
#include <sys/ioctl.h>
#include <getopt.h>
#include "image.h"

int fds;

int serialport_init(const char* serialport, int baud);
int serialport_write(int fd, unsigned char* buf);

int initiateSerialLine()
{
  fds = 0;
  char serialport[256];
  int baudrate = B115200;  

		
  fds = serialport_init("/dev/ttyACM0", baudrate);
  if(fds==-1) return -1;
  return 0;
}

int closeSerialLine()
{
  close(fds);
  return 0;
}



int sendToArduino(unsigned char* buffer)
{
	
	//	usleep(3000 * 1000 );
	
	//Code for reading in values to be sent to arduino.
  int rc;	
  rc = serialport_write(fds, buffer);
  
  if(rc==-1) return -1;
  return 0;
}

int serialport_write(int fd, unsigned char* buf)
{
    int len = strlen(buf);	
    int n = write(fd, buf, len);
	
    if( n!=len ) 		
        return -1;	
    return n;
}

int serialport_init(const char* serialport, int baud)
{
	
    struct termios toptions;	
    	int fd;
	
	fd = open(serialport, O_RDWR | O_NOCTTY);
	
    if (fd == -1)  {	
        perror("Port could not be opened");	
        return -1;		
    }
	
    if (tcgetattr(fd, &toptions) < 0) {	
        perror("Couldn't get term attributes");	
        return -1;		
    }
	
    speed_t brate = baud; 

    switch(baud) {
			
		case 4800:   brate=B4800;   break;	
		case 9600:   brate=B9600;   break;	
		case 19200:  brate=B19200;  break;
		case 38400:  brate=B38400;  break;	
		case 57600:  brate=B57600;  break;	
		case 115200: brate=B115200; break;
    }
	
    cfsetispeed(&toptions, brate);
	
    cfsetospeed(&toptions, brate);
	
	
    // 8N1
	
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
	
    // no flow control
	
    toptions.c_cflag &= ~CRTSCTS;
	
	
	
    toptions.c_cflag |= CREAD | CLOCAL;  
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); 
	
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
    toptions.c_oflag &= ~OPOST; 
		
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;

    
    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
        perror("Couldn't set term attributes");
        return -1;	
    }
		
	
    return fd;
	
}
