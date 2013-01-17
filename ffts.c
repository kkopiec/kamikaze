#include<math.h>
#include<stdlib.h>
#include<fftw3.h>
#include<string.h>

#include "ffts.h"
#include "grab.h"
#include "windows.h"
#include "global.h"

#define	MAX_WIDTH	8192
#define	MAX_HEIGHT	4096

fftw_plan plan;
//fftw_complex *out;
double *in, *out;
int fft_set = 0;

void
apply_window (double * data, int datalen)
{
  static double window [10 * MAX_HEIGHT] ;
  static int window_len = 0 ;
  int k ;
  
  if (window_len != datalen)
    {
      window_len = datalen ;
      if (datalen > ARRAY_LEN (window))
	{
	  printf ("%s : datalen >  MAX_HEIGHT\n", __func__) ;
	  exit (1) ;
	} ;

      calc_kaiser_window (window, datalen, 20.0) ;
    } ;
  
  for (k = 0 ; k < datalen ; k++)
    data [k] *= window [k] ;
  
  return ;
}

double
calc_magnitude (const double * freq, int freqlen, double * magnitude)
{
  int k ;
  double max = 0.0 ;
  
  for (k = 1 ; k < freqlen / 2 ; k++)
    {	magnitude [k] = sqrt (freq [k] * freq [k] + freq [freqlen - k - 1] * freq [freqlen - k - 1]) ;
      max = MAX (max, magnitude [k]) ;
    } ;
  magnitude [0] = 0.0 ;
  
  return max ;
}

void 
fftw_setup(int length)
{
  int N = length;
  in = malloc(sizeof(double) * N);
  out = malloc(sizeof(double) * N);

  fft_set = 1;
}

int
getfreq(double *sin, double* sout, int length)
{
  if (!fft_set)
    fftw_setup(length);
  plan = fftw_plan_r2r_1d (length , sin, sout, FFTW_R2HC, FFTW_MEASURE) ;
  memcpy(in, sin, length);
  fftw_execute(plan);
  memcpy(out, sout, length);
  fftw_destroy_plan (plan);
  return length * 2;
}

void
fft_clean()
{
  if (fft_set)
    ;
}
 
