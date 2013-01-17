#include <stdlib.h>
#include "image.h"

/*******************************************************************************
 * starts at full power on the first slite
 * and then gradually fades out towards the end of the cube
 ******************************************************************************/
void
fallingEdge(struct image *img, int *mag, int size)
{
  dshifttop(img);
  rshift(img);
  int i;
  for(i = 0 ; i < 8 ; i++){
    if(mag[i] <0)
      mag[i] = 0;
    if(mag[i] >7)
      mag[i] = 7;
    clear_column(img,0,i);
    set_column(img,0,i,mag[i]);
  }
  return;
}

/*******************************************************************************
 * registers db on the first slate
 * and holds it up to the last slate
 ******************************************************************************/
void
plainDb(struct image *img, int *mag, int size)
{
  rshift(img);
  int i;
  for(i = 0 ; i < 8 ; i++){
    if(mag[i] <0)
      mag[i] = 0;
    if(mag[i] >7)
      mag[i] = 7;
    clear_column(img,0,i);
    set_column(img,0,i,mag[i]);
  }
  return;
}
