#include <cstdlib>
#include <cmath>

#include "mpi.h"

#include <iostream>

using namespace std;

#define N 840

int main(void)
{
  double pi, exactpi;

  int i;

  // MPI variables

  MPI_Comm comm;
  MPI_Status status;

  int rank, size, source, tag, namelen;
  char nodename[MPI_MAX_PROCESSOR_NAME];

  // Other variables

  int istart, istop;
  double partialpi, recvpi;

  cout << "Computing approximation to pi using N = " << N << endl;

  // Initialise MPI and compute number of processes and local rank

  comm = MPI_COMM_WORLD;

  MPI_Init(NULL, NULL);

  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);
  MPI_Get_processor_name(nodename, &namelen);
  
  cout << "Hello from rank " << rank << " on node <" << nodename << ">" << endl;

  // Now make sure output only comes from one process

  if (rank == 0) cout << "Running on " << size << " process(es)" << endl;

  partialpi = 0.0;

  //
  // Compute an approximation to pi using a simple series expansion for pi/4
  // Ensure each process computes a separate section of the summation
  // NOTE: here I assume that N is exactly divisible by the number of processes
  //

  istart = N/size * rank + 1;
  istop  = istart + N/size - 1;

  cout << "On rank " << rank << " istart = " << istart
       << ", istop = " << istop << endl;

  for (i=istart; i<=istop; i++)
    {
      partialpi = partialpi +
	          1.0/( 1.0 + pow( (((double) i)-0.5)/((double) N), 2.0) );
    }

  cout << "On rank " << rank << " partialpi = " << partialpi << endl;

  //
  // Compute global value of pi by sending partial values to rank 0 
  // NOTE: this would be more efficiently done using MPI_REDUCE 
  //

  if (rank == 0)
    {
      // Initialise pi to locally computed parial sum

      pi = partialpi;

      // Add in contribution from other processes

      for (source = 1; source < size; source++)
	{
	  // receive partialpi from rank=source and place value in recvpi
	  // all messages are tagged as zero

	  tag = 0;

	  MPI_Recv(&recvpi, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag, comm, &status);

	  cout << "rank 0 receiving from rank " << status.MPI_SOURCE << endl;

	  // add to running total

	  pi = pi + recvpi;
	}
    }
  else
    {
      // all other processes send their partial value to rank 0

      tag = 0;

      cout << "rank " << rank << " sending to rank 0" << endl;

      MPI_Ssend(&partialpi, 1, MPI_DOUBLE, 0, tag, comm);
    }

  pi = pi * 4.0/((double) N);

  exactpi = 4.0*atan(1.0);
  
  if (rank == 0)
    {
      cout << "pi = " << pi
	   << ", % error = " << fabs(100.0*(pi-exactpi)/exactpi) << endl;
    }

  MPI_Finalize();

  return 0;
}
