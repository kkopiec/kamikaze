#include<math.h>
#include<stdlib.h>
#include<fftw3.h>
#include<string.h>
#include"ffts.h"
#include"grab.h"
fftw_plan plan;
//fftw_complex *out;
double *in, *out;
int fft_set = 0;

static double
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
  out = malloc(sizeof(double) * N * 2);
  plan = fftw_plan_r2r_1d (N , in, out, FFTW_R2HC, FFTW_MEASURE | FFTW_PRESERVE_INPUT) ;
  fft_set = 1;
}

int
getfreq(double *sin, double* sout, int length)
{
  if (!fft_set)
    fftw_setup(length);
  memcpy(in, sin, length);
  fftw_execute(plan);
  memcpy(out, sout, length *2);
  return length * 2;
}

void
fft_clean()
{
  if (fft_set)
    fftw_destroy_plan (plan);
}
 
