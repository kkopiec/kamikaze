#include<math.h>
#include<fftw3.h>
#include"grab.h"
fftw_plan plan;
static float
calc_magnitude (const float * freq, int freqlen, float * magnitude)
{
	int k ;
	float max = 0.0 ;

	for (k = 1 ; k < freqlen / 2 ; k++)
	{	magnitude [k] = sqrt (freq [k] * freq [k] + freq [freqlen - k - 1] * freq [freqlen - k - 1]) ;
		max = MAX (max, magnitude [k]) ;
		} ;
	magnitude [0] = 0.0 ;

	return max ;
}
void fftw_setup()
{
  plan = fftw_plan_r2r_1d (2 * speclen, time_domain, freq_domain, FFTW_R2HC, FFTW_MEASURE | FFTW_PRESERVE_INPUT) ;
}

int getfreq(float* sin, float* sout, int size)
{
  
