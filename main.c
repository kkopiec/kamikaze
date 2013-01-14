#include<stdlib.h>
#include<stdio.h>

#include"grab.h"
void cb_mic(struct audio_stream *as)
{
  printf("got call from grabber, received buffer of %d samples\n", as->buffer_length);
}
int
main (int argc, char *argv[])
{
  mic_setup (&cb_mic);
  mic_grab;
  while (1)
    sleep (1);
  return 0;
}
