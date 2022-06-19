#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 840

int main(void)
{
  double pi, exactpi;

  int i;

  printf("Computing approximation to pi using N = %d\n", N);

  pi = 0.0;

  for (i=1; i<=N; i++)
    {
      pi = pi + 1.0/( 1.0 + pow( (((double) i)-0.5)/((double) N), 2.0) );
    }

  pi = pi * 4.0/((double) N);

  exactpi = 4.0*atan(1.0);
  
  printf("pi = %f, %% error = %f\n", pi, fabs(100.0*(pi-exactpi)/exactpi));

  return 0;
}
