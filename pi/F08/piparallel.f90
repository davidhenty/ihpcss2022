program piparallel

  use mpi_f08

  implicit none

  integer, parameter :: N = 840
  integer :: i

! MPI variables

  integer :: rank, size, source, tag, namelen
  integer :: realsize

  type(MPI_Comm)     :: comm
  type(MPI_Status)   :: status
  type(MPI_Datatype) :: mpirealtype
  character*(MPI_MAX_PROCESSOR_NAME) :: nodename
  
! Other local variables

  integer :: istart, istop
  real(kind=8) :: pi, exactpi, partialpi, recvpi

  write(*,*) 'Computing approximation to pi using N = ', N

! Initialise MPI and compute number of processes and local rank

  comm = MPI_COMM_WORLD

  call MPI_Init()

  call MPI_Comm_size(comm, size)
  call MPI_Comm_rank(comm, rank)
  call MPI_Get_processor_name(nodename, namelen)

  write(*,*) "Hello from rank ", rank, " on node <", nodename(1:namelen), ">"

! Now make sure output only comes from one process

  if (rank == 0) write(*,*) 'Running on ', size, ' process(es)'

  partialpi = 0.0d0

! We could just set mpirealtype = MPI_DOUBLE_PRECISION but the
! following code is more general and will still work even if we
! change the Fortran definitions of pi etc. to single precision.

  call MPI_Sizeof(pi, realsize)
  call MPI_Type_match_size(MPI_TYPECLASS_REAL, realsize, mpirealtype)

!  Compute an approximation to pi using a simple series expansion for pi/4
!  Ensure each process computes a separate section of the summation
!  NOTE: here I assume that N is exactly divisible by the number of processes

  istart = N/size * rank + 1
  istop  = istart + N/size - 1

  write(*,*) 'On rank ', rank, ' istart = ', istart, ', istop = ', istop

  do i = istart, istop

     partialpi = partialpi + 1.0d0/(1.0d0+((dble(i)-0.5d0)/dble(N))**2)

  end do

  write(*,*) 'On rank ', rank, ' partialpi = ', partialpi * 4.0d0/dble(N)

! Compute global value of pi by sending partial values to rank 0
! NOTE: this would be more efficiently done using MPI_REDUCE

  if (rank == 0) then

! initialise pi to locally computed partial sum

    pi = partialpi

! add in contributions from other processes

    do source = 1, size-1

! receive partialpi from *any* source and place value in recvpi
! all messages are tagged as zero

       tag = 0

       call MPI_Recv(recvpi, 1, mpirealtype, MPI_ANY_SOURCE, &
                     tag, comm, status)

       write(*,*) 'rank 0 receiving from rank ', status%MPI_SOURCE

! add to running total

       pi = pi + recvpi

    end do

  else

! all other processes send their partial value to rank 0

     write(*,*) 'rank ', rank, ' sending to rank 0'

     tag = 0

     call MPI_Ssend(partialpi, 1, mpirealtype, 0, tag, comm)

  end if

  pi = pi * 4.0d0/dble(N)

  exactpi = 4.0d0*atan(1.0d0)

  if (rank == 0) then
     write(*,*) 'pi = ', pi, ', % error = ', abs(100.0d0*(pi-exactpi)/exactpi)
  end if

! Finalise MPI

  call MPI_Finalize()

end program piparallel
