#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "grab.h"
#include "ffts.h"
#include "windows.h"
#include "global.h"
#include "image.h"
#include "animation.h"
struct image *img;

void 
calculate_fbs(int samplerate, int buffer_length)
{
  int i;
  for (i = 0; i < buffer_length /2; i++){
    double fq = i * samplerate / buffer_length;
    printf("%d\t%f Hz\n",i,fq);
  }
}
void cb_mic(struct audio_stream *as)
{
  double *freq = malloc(sizeof(double) * as->buffer_length);
  apply_window (as->audio_data, as->buffer_length);
  int tl = getfreq(as->audio_data, freq, as->buffer_length);
  double *magd = malloc(sizeof(double)* as->buffer_length);
  double max = calc_magnitude(freq, as->buffer_length, magd);
  //  printf("Got %d frequencies at %d of %d audio frames\n", tl/2, as->sample_rate, as->buffer_length);
  int mag[8];
  mag[0] = 8 + (int) round(log10(magd[1]));
  mag[1] = 8 + (int) round(log10(magd[2]));
  mag[2] = 8 + (int) round(log10(magd[4]));
  mag[3] = 8 + (int) round(log10(magd[9]));
  mag[4] = 8 + (int) round(log10(magd[21]));
  mag[5] = 8 + (int) round(log10(magd[53]));
  mag[6] = 8 + (int) round(log10(magd[171]));
  mag[7] = 8 + (int) round(log10(magd[213]));
  //  printf("%d,%d,\n%d,%d,\n%d,%d,\n%d,%d\n",mag[0],mag[1],mag[2],mag[3],mag[4],mag[5],mag[6],mag[7]);
  //  printf("--------------------------------------------------------------\n\n");

  // make animation here
  
  fallingEdge(img, mag, 8);

  // send img somewhere here
  testimgdisplay(img);
  printf("\n");
 /*
  int j = sizeof(double) * as->buffer_length ;
  int j0 ;
  for (j0 = 0; j0 < j ; j0++){
    printf("%f", freq[j0]);
  }
  printf("\n\n");
  */
  free(freq);
  
}
int
main (int argc, char *argv[])
{
  img = malloc( sizeof(struct image));
  img->width = 8;
  img->height = 8;
  img->frames = 8;
  int datasize = img->width * img->height * img->frames;
  img->imgdata = calloc(datasize, sizeof(char));

  fftw_setup(1024);
  mic_setup (&cb_mic);
  //mic_grab;
  //calculate_fbs(48000, 1024);
  while (1)
    sleep (1);
  free(img);
  return 0;
}
