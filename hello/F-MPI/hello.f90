program hello

  use mpi

  implicit none

  integer :: size, rank, ierr
  integer :: comm = MPI_COMM_WORLD

  call MPI_Init(ierr)
  call MPI_Comm_size(comm, size, ierr)
  call MPI_Comm_rank(comm, rank, ierr)

  if (rank == 0) write(*,*) "Running on ", size, " process(es)"
  write(*,*) "Hello from rank ", rank, "!"

  call MPI_Finalize(ierr)

end program hello
