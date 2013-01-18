#include <stdio.h>
#include "compressor.h"
#include "image.h"

int main(){
  char td[]={0,0,0,0,0,0,0,1};
  struct image udata;
  udata.width = 2;
  udata.height = 2;
  udata.frames = 2;
  udata.imgdata = (char*) td;

  unsigned char *codata = compressData( &udata );

  printf ("got: %u\n", codata[0]);
  return 0;
}
