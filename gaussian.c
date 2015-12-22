#include <stdio.h>
#include <math.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_statistics.h>

#define N (4096*4*16)

double g (double *x, int dim);

int
main (void)
{
  double sum;
  double s = 12.;
  int dim = 4;
  double x[4];

  gsl_rng *r;

  r = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (r, 1UL);

  long i, j, nn;

  printf ("# Iter        Npoints   Volume     AbsErr\n");
  nn = N;
  for (j = 0; j < 16; j++)
    {
      sum = 0.;
      for (i = 0; i < nn; i++)
	{
	  // 4-dimensional random point
	  for (int k = 0; k < dim; k++)
	    {
	      x[k] = s * gsl_rng_uniform (r) - s / 2;
	    }
	  sum += g (x, dim);
	}
      double integ = (sum * pow (s, (double) dim)) / nn;
      double exact = M_PI * M_PI;

      printf ("%3ld  %16ld   %f   %f\n", j, nn, integ, fabs (exact - integ));
      nn *= 2;
    }

  gsl_rng_free (r);

  return 0;
}

double
g (double *x, int dim)
{
  double r2 = 0., q;

  for (int i = 0; i < dim; i++)
    {
      q = x[i];
      r2 += q * q;
    }

  return exp (-r2);
}
