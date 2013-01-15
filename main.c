#include<stdlib.h>
#include<stdio.h>

#include"grab.h"
#include "ffts.h"
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

  //  printf("got call from grabber, received buffer of %d samples\n", as->buffer_length);
  /*  printf ("%f",as->audio_data[0]);
  int i;
  for (i = 1; i < as->buffer_length; i++){
    printf(",%f", as->audio_data[i]);
    if ((i % 8) == 0)
      printf("\n");
  }
  printf("===============================================================================\n");
  */
  printf(",%f\n\n\n", as->audio_data[1]);
  double *freq = malloc(sizeof(double) * as->buffer_length * 2);
  int tl = getfreq(as->audio_data, freq, as->buffer_length);
  //  printf("Got %d frequencies at %d of %d audio frames\n", tl/2, as->sample_rate, as->buffer_length);
  //printf("%f,%f,%f,%f,%f,%f,%f,%f\n",freq[1],freq[2],freq[4],freq[9],freq[21],freq[53],freq[171],freq[213]);
  int j = sizeof(double) * as->buffer_length * 2;
  int j0 ;
  for (j0 = 0; j0 < j ; j0++){
    printf("%f", freq[j0]);
  }
  printf("\n\n");

  free(freq);
}
int
main (int argc, char *argv[])
{
  fftw_setup(1024);
  mic_setup (&cb_mic);
  //mic_grab;
  //calculate_fbs(48000, 1024);
  while (1)
    sleep (1);
  return 0;
}
