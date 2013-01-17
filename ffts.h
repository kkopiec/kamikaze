#ifndef FFTS_H
#define FFTS_H

#define MAX(x,y)		((x) > (y) ? (x) : (y))
#define MIN(x,y)		((x) < (y) ? (x) : (y))

double 
calc_magnitude (const double * freq, int freqlen, double * magnitude);

void 
fftw_setup(int length);

int 
getfreq(double *sin, double* sout, int length);

void
fft_clean();

void
apply_window (double * data, int datalen);
#endif
