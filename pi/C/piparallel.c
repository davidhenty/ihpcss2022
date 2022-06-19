#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <mpi.h>

#define N 840

int main(void)
{
  double pi, exactpi;

  int i;

  /* MPI variables */

  MPI_Comm comm;
  MPI_Status status;

  int rank, size, source, tag, namelen;
  char nodename[MPI_MAX_PROCESSOR_NAME];

  /* Other variables */

  int istart, istop;
  double partialpi, recvpi;

  printf("Computing approximation to pi using N = %d\n", N);

  /* Initialise MPI and compute number of processes and local rank */

  comm = MPI_COMM_WORLD;

  MPI_Init(NULL, NULL);

  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);
  MPI_Get_processor_name(nodename, &namelen);
  
  printf("Hello from rank %d on node <%s>\n", rank, nodename);

  /* Now make sure output only comes from one process */

  if (rank == 0) printf("Running on %d process(es)\n", size);

  partialpi = 0.0;

  /*
   * Compute an approximation to pi using a simple series expansion for pi/4
   * Ensure each process computes a separate section of the summation
   * NOTE: here I assume that N is exactly divisible by the number of processes
   */

  istart = N/size * rank + 1;
  istop  = istart + N/size - 1;

  printf("On rank %d istart = %d, istop = %d\n", rank, istart, istop);

  for (i=istart; i<=istop; i++)
    {
      partialpi = partialpi +
	          1.0/( 1.0 + pow( (((double) i)-0.5)/((double) N), 2.0) );
    }

  printf("On rank %d partialpi = %f\n", rank, partialpi*4.0/((double) N));

  /*
   * Compute global value of pi by sending partial values to rank 0 
   * NOTE: this would be more efficiently done using MPI_REDUCE 
   */

  if (rank == 0)
    {
      /* Initialise pi to locally computed parial sum */

      pi = partialpi;

      /* Add in contribution from other processes */

      for (source = 1; source < size; source++)
	{
	  /* receive partialpi from *any* source and place value in recvpi */
	  /* all messages are tagged as zero */

	  tag = 0;

	  MPI_Recv(&recvpi, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag, comm, &status);

	  printf("rank 0 receiving from rank %d\n", status.MPI_SOURCE);

	  /* add to running total */

	  pi = pi + recvpi;
	}
    }
  else
    {
      /* all other processes send their partial value to rank 0 */

      tag = 0;

      printf("rank %d sending to rank 0\n", rank);

      MPI_Ssend(&partialpi, 1, MPI_DOUBLE, 0, tag, comm);
    }

  pi = pi * 4.0/((double) N);

  exactpi = 4.0*atan(1.0);
  
  if (rank == 0)
    {
      printf("pi = %f, %% error = %f\n", pi, fabs(100.0*(pi-exactpi)/exactpi));
    }

  MPI_Finalize();

  return 0;
}
