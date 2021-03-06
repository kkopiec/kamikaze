#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "windows.h"
#include "global.h"

static double besseli0 (double x);
static double factorial (int val);

void
calc_kaiser_window (double * data, int datalen, double beta)
{
	/*
	**          besseli0 (beta * sqrt (1- (2*x/N).^2))
	** w (x) =  --------------------------------------,  -N/2 <= x <= N/2
	**                 besseli0 (beta)
	*/

	double two_n_on_N, denom ;
	int k ;

	denom = besseli0 (beta) ;

	if (! isfinite (denom))
	{	printf ("besseli0 (%f) : %f\nExiting\n", beta, denom) ;
		exit (1) ;
		} ;

	for (k = 0 ; k < datalen ; k++)
	{	double n = k + 0.5 - 0.5 * datalen ;
		two_n_on_N = (2.0 * n) / datalen ;
		data [k] = besseli0 (beta * sqrt (1.0 - two_n_on_N * two_n_on_N)) / denom ;
		} ;

	return ;
} /* calc_kaiser_window */

void
calc_nuttall_window (double * data, int datalen)
{
    const double a [4] = { 0.355768, 0.487396, 0.144232, 0.012604 } ;
	int k ;

	/*
	**	Nuttall window function from :
	**
	**	http://en.wikipedia.org/wiki/Window_function
	*/

	for (k = 0 ; k < datalen ; k++)
	{	double scale ;

		scale = M_PI * k / (datalen - 1) ;

		data [k] = a [0] - a [1] * cos (2.0 * scale) + a [2] * cos (4.0 * scale) - a [3] * cos (6.0 * scale) ;
		} ;

	return ;
} /* calc_nuttall_window */

/*==============================================================================*/

static double
besseli0 (double x)
{
	int k ;
	double result = 0.0 ;

	for (k = 1 ; k < 25 ; k++)
	{	double temp ;

		temp = pow (0.5 * x, k) / factorial (k) ;
		result += temp * temp ;
		} ;

	return 1.0 + result ;
} /* besseli0 */

static double
factorial (int val)
{	static double memory [64] = { 1.0 } ;
	static int have_entry = 0 ;

	int k ;

	if (val < 0)
	{	printf ("Oops : val < 0.\n") ;
		exit (1) ;
		} ;

	if (val > ARRAY_LEN (memory))
	{	printf ("Oops : val > ARRAY_LEN (memory).\n") ;
		exit (1) ;
		} ;

	if (val < have_entry)
		return memory [val] ;

	for (k = have_entry + 1 ; k <= val ; k++)
		memory [k] = k * memory [k - 1] ;

	return memory [val] ;
} /* factorial */

/*==============================================================================*/

static void init_test (void) __attribute__ ((constructor)) ;

static void
init_test (void)
{
	/* puts (__func__) ;*/

	assert (factorial (0) == 1.0) ;
	assert (factorial (2) == 2.0) ;
	assert (factorial (0) == 1.0) ;
	assert (factorial (5) == 120.0) ;
	assert (factorial (8) == 40320.0) ;

	assert (fabs (besseli0 (0.0) - 1.0) < 1e-8) ;
	assert (fabs (besseli0 (0.5) - 1.06348337074132) < 1e-8) ;
	assert (fabs (besseli0 (1.0) - 1.26606587775201) < 1e-14) ;
	assert (fabs (besseli0 (2.0) - 2.27958530233607) < 1e-14) ;
	assert (fabs (besseli0 (3.5) - 7.37820343222548) < 1e-14) ;

} /* init_test */

