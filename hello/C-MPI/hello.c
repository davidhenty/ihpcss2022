#include <stdio.h>
#include <mpi.h>

int main(void)
{
  int rank, size;
  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Init(NULL,NULL);
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);

  if (rank == 0) printf("Running on %d process(es)\n", size);
  printf("Hello from rank %d!\n", rank);

  MPI_Finalize();

  return 0;
}
