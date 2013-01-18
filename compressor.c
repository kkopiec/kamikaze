#include <stdlib.h>
#include <string.h>
#include "compressor.h"
#include <stdio.h>

unsigned char*
compressData(struct image *img)
{

    char *data = img->imgdata; //bitmap data
    int iw = img->width;       //width
    int ih = img->height;      //height
    int imf = img->frames;      //no of frames

    int clen = iw*ih*imf;
    int rlen = clen/8;

    unsigned char *ret = malloc(rlen);
    memset(ret,0,rlen);
    int i;
    for (i=0 ; i<clen; i++){
      if (data[i]==1){
	ret[i/8] |= 1 << (i%8);
      }
    }
    return ret;
}
