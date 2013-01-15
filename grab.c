#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <jack/jack.h>
#include "grab.h"
jack_client_t *client;
jack_port_t *input_port;
float *adata;
void (*dataproc)(struct audio_stream*);
/***********************
 * callback function from jack audio server on data retrieval
 ***********************/
int 
process (jack_nframes_t nframes, void *arg)
{
  jack_default_audio_sample_t *in = (jack_default_audio_sample_t *) jack_port_get_buffer (input_port, nframes);
  struct audio_stream *adata = malloc(sizeof(struct audio_stream));
  adata->audio_data = malloc(sizeof(jack_default_audio_sample_t) * nframes);
/*  adata = malloc(sizeof(jack_default_audio_sample_t) * nframes);*/
  adata->buffer_length = nframes;
  adata->sample_rate = jack_get_sample_rate(client);
  memcpy (adata->audio_data, in, sizeof(jack_default_audio_sample_t) * nframes);
  /*********************** TODO ***********************
   * here we've got data from the mic (adata) of the length nframes
   * good to send back (maybe callback ??)
   ****************************************************/
  /* printf("Data: %f\n", adata[0]); */

  /***********************
   * call callback function
   * to work over data
   ***********************/
  (*dataproc) (adata);
  free(adata->audio_data);
  free(adata);
  return 0;
}

/***********************
 * callback function from jack audio server on shutdown
 ***********************/
void 
jack_shutdown(void *arg)
{
  exit(1);
}

/***********************
 * setup ports etc
 ***********************/
int
mic_setup( void (*dpf)(struct audio_stream*) )
{
  dataproc = dpf;

  /***********************
   * create jack client for the server
   ***********************/
  if ((client = jack_client_open("kamikaze", JackNullOption,NULL)) == NULL){
    fprintf(stderr, "jack server not running?/nOr maybe should try this as root?/n");
    return 1;
  }

  jack_set_process_callback(client, process, 0);
  jack_on_shutdown(client, jack_shutdown,0);
  input_port = jack_port_register(client, "mic", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput,0);

  if (jack_activate(client)){
    fprintf(stderr, "cannot activate client!\n");

    exit(1);
  }
  mic_grab();

}

/***********************
 * start capturing
 ***********************/
void mic_grab()
{
  const char **ports;
  if ((ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput)) == NULL){
    fprintf(stderr, "Cannot find phisical capture ports!\n");
    exit(1);
  }

  if (jack_connect(client, ports[0], jack_port_name(input_port))){
    fprintf(stderr,"Cannot connect input ports!\n");
    exit(1);
  }
}
