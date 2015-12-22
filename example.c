#include <stdio.h>
#include <math.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_statistics.h>

#define N (4096*4*16)

int main (void)
{
    long countsq;
    double x, r2;
    //6 dimensional space
    int dim = 6;

    gsl_rng *r;

    r = gsl_rng_alloc (gsl_rng_taus2);
    gsl_rng_set (r, 1UL);

    long i, j, nn;

    printf ("# Iter        Npoints   Volume     AbsErr\n");
    nn = N;
    for (j = 0; j < 16; j++)
    {
        countsq = 0L;
        for (i = 0; i < nn; i++)
        {
            // 4-dimensional distance from the origin, squared
            r2 = 0.;
            for (int k = 0; k < dim; k++)
            {
                x = 2 * gsl_rng_uniform (r) - 1.;
                r2 += x * x;
            }

            // are we inside the unit ball
            if (r2 <= 1.)
            {
                countsq++;
            }
        }
        // ratio of the volume of the 4-dimensional unit ball and 
        // and 4-dimensional cube of side length 2.
        double vol = ((double) countsq) * pow (2, (double) dim) / nn;
        double exact = M_PI * M_PI / 2;

        printf ("%3ld  %16ld   %f   %f\n", j, nn, vol, fabs (exact - vol));
        nn *= 2;
    }

    gsl_rng_free (r);

    return 0;
}
