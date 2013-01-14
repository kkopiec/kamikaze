#ifndef GRAB_H
#define GRAB_H

struct audio_stream {
  unsigned int buffer_length;
  unsigned int sample_rate;
  float *audio_data;
};
int mic_setup ( void (*dpf)(struct audio_stream*) );
void mic_grab (void);
#endif
