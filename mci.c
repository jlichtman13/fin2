#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_vegas.h>
#include "integral.c"
#include "timer.c"
#include "timer.h"
#define N 20
double g (double *t,size_t dim, void *params);

int main (void)
{
	double res, err;
	// 6 dimensional integral
	size_t dim = 6;

	int dims=6;
	//evaluating all dimensions from 0 to 1
	double x1[] = { 0., 0., 0. ,0.,0.,0. };
	double xu[] = { 1., 1., 1. ,1.,1.,1. };
	FILE *file;
	file=fopen("data.txt","w");

	double rmin=1.001;
	double rmax=4;
	double rtot=rmin;
	double rstep= (rmax-rmin)/(N);

	gsl_rng *r = gsl_rng_alloc (gsl_rng_taus2);
	unsigned long seed = 1UL;
	gsl_rng_set (r, seed);

	// 10^6 function evaluations per iteration

	size_t calls = 1000000;
	gsl_monte_function G= { &g, dim, &rtot};
	gsl_monte_vegas_state *sv = gsl_monte_vegas_alloc (dim);
	gsl_monte_vegas_init (sv);

	//Vegas integration
	double vegas[N];
	double rval[N];
	double di[N];
	timer_start ();
	for (int i = 0; i<=N-1; i++)
	{
		gsl_monte_vegas_integrate (&G,x1,xu,dim,calls/5,r,sv,&res,&err);
		do 
		{
			gsl_monte_vegas_integrate (&G, x1,xu,dim,calls,r,sv,&res,&err);
			fflush (stdout);
		}

		while (fabs (gsl_monte_vegas_chisq (sv)-1.0) >0.2);
		rtot+=rstep;
		vegas[i]=res;
		rval[i]=rtot;
		di[i] = -.2 / pow (rtot,3.);
	}
	timer_stop ();
	double tvegas=timer_stop();
	gsl_monte_vegas_free (sv);
	rtot=rmin;
	printf (" %10.6f\n",tvegas);
	//homemade
	rtot=rmin;	
	double x[6];


   	r = gsl_rng_alloc (gsl_rng_taus2);
   	gsl_rng_set (r, 1UL);
	double thome;
	long i, j;
	double r2=0.;
	double home[20];
	for (j = 0; j < N; j++)
   	{
		r2=0.;
       		for (i = 0; i < 1.e6; i++)
        	{
            		for (int k = 0; k <= dims; k++)
            		{
                		x[k] = gsl_rng_uniform (r) ;
            		}
		r2+= g(x,dim, &rtot);
		
        }
       res = r2/1.e6;
	fflush (stdout);
	rtot+=rstep;
	home [j]=res;
    }
	timer_stop();
	rtot=rmin;
	thome=timer_stop();
	printf (" %10.6f\n",thome);
	for (int t=0;t<N;t++)
        {
                fprintf (file, "%10.6f     %10.6f    %10.6f  %10.6f \n " , rval[t],fabs(-vegas[t]),fabs(-di[t]),fabs(-home[t]));
                rtot+=rstep;
        }



	return 0;
}
