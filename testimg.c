#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"

struct image* img;

int main(){

  img = malloc( sizeof(struct image));
  img->width = 8;
  img->height = 8;
  img->frames = 8;
  int datasize = img->width * img->height * img->frames;
  img->imgdata = calloc(datasize, sizeof(char));

  set_column(img,0,0,3);
  testimgdisplay(img);
  rshift(img);
  set_column(img,0,1,6);
  testimgdisplay(img);
  rshift(img);
  set_column(img,0,1,2);
  testimgdisplay(img);
  return;
}
