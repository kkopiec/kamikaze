#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"

/*******************************************************************************
 * Set bit of
 * image: img
 * in frame: frame
 * on position
 * width: w
 * height: h
 *******************************************************************************/ 
void 
set_bit(struct image *img, int frame, int w, int h, int bit)
{
  char *data = img->imgdata; //bitmap data
  int iw = img->width;       //width
  int ih = img->height;      //height
  int imf = img->frames;      //no of frames

  if (frame > imf){
    fprintf(stderr, "Error: out of bounds. Trying to write to the frame no: %d but the last frame is %d\n", frame, imf -1);
    exit -1;
  }
  int pn; //pixel location index
  pn = (frame * ih * iw) + ((h*iw) +w);
  data[pn] = bit;
  return;
}

/******************************************************************************
 * get bit from particular location
 *****************************************************************************/
int 
get_bit(struct image *img, int frame, int w, int h)
{
  char *data = img->imgdata; //bitmap data
  int iw = img->width;       //width
  int ih = img->height;      //height
  int imf = img->frames;      //no of frames

  if (frame > imf){
    fprintf(stderr, "Error: out of bounds. Trying to write to the frame no: %d but the last frame is %d\n", frame, imf -1);
    exit -1;
  }
  int pn; //pixel location index
  pn = (frame * ih * iw) + ((h*iw) +w);
  return (int)data[pn];
}

/********************************************************************************
 * drop last frame and shift all other frames to the right
 *******************************************************************************/
void 
rshift(struct image *img)
{
  char *data = img->imgdata; //bitmap data
  int iw = img->width;       //width
  int ih = img->height;      //height
  int imf = img->frames;      //no of frames
  int fr_length = ih * iw;
  memmove(data + fr_length, data, (imf-1)* fr_length*sizeof(char));
  memset(data, 0, fr_length * sizeof(char));
  return;
}


/*******************************************************************************
 * clear column at w
 ******************************************************************************/
void 
clear_column (struct image *img, int frame, int w) 
{
  char *data = img->imgdata; //bitmap data
  int iw = img->width;       //width
  int ih = img->height;      //height
  int imf = img->frames;      //no of frames
  
  if (frame > imf){
    fprintf(stderr, "Error: out of bounds. Trying to write to the frame no: %d but the last frame is %d\n", frame, imf -1);
    exit -1;
  }
  int h = ih;
  while (h >= 0){
    set_bit(img,frame,w,h,0);
    h-=1;
  }
  return;
}




/*******************************************************************************
 * set whole column up to the (including) the point (w,h)
 ******************************************************************************/
void 
set_column (struct image *img, int frame, int w, int h)
{
  char *data = img->imgdata; //bitmap data
  int iw = img->width;       //width
  int ih = img->height;      //height
  int imf = img->frames;      //no of frames
  if (frame > imf){
    fprintf(stderr, "Error: out of bounds. Trying to write to the frame no: %d but the last frame is %d\n", frame, imf -1);
    exit -1;
  }
  while (h >= 0){
    set_bit(img,frame,w,h,1);
    h-=1;
  }
  return;
}


void 
testimgdisplay(struct image *img)
{
  char *data = img->imgdata; //bitmap data
  int iw = img->width;       //width
  int ih = img->height;      //height
  int imf = img->frames;      //no of frames

  int row, col, slate;
  for(row = 0; row < ih; row++){
    for(slate = 0; slate < imf; slate++){
      for(col = 0; col < iw; col++){
	int c = get_bit(img,slate,col,row);
	if(c != 0){
	  printf("X");
	} else
	  { 
	    printf(" ");
	  }
      }
      printf(" | ");
    }
    printf("\n");
  }
  return;
}

void 
dshifttop (struct image* img)
{
  char *data = img->imgdata; //bitmap data
  int iw = img->width;       //width
  int ih = img->height;      //height
  int imf = img->frames;      //no of frames
  
  int bufsize = iw*ih*imf;
  int w,h;
  //  int pn = (frame * ih * iw) + ((h*iw) +w);
  int frame,col,row;
  for (frame = 0; frame < imf; frame++){
    for(col = 0; col < iw; col++){
      for(row = 7; row > 0 ; row--){
	int c;
	if((c= get_bit(img, frame,col,row)) != 0){
	    set_bit(img, frame, col,row,0);
	    break;
	  }
      }
    }
  }	  
  return;
}
