program hello

  use omp_lib

  implicit none

  !$omp parallel

  !$omp master
  write(*,*) "Running on ", omp_get_num_threads(), " threads"
  !$omp end master

  write(*,*) "Hello from thread ", omp_get_thread_num()

  !$omp end parallel

end program hello

