program piserial

  implicit none

  integer, parameter :: N = 840

  double precision :: pi, exactpi

  integer :: i

  write(*,*) 'Computing approximaton to pi using N = ', N

  pi = 0.0d0

!  Compute an approximation to pi using a simple series expansion for pi/4

  do i = 1, N

     pi = pi + 1.0d0/(1.0d0+((dble(i)-0.5d0)/dble(N))**2)

  end do

  pi = pi * 4.0d0/dble(N)

  exactpi = 4.0d0*atan(1.0d0)

  write(*,*) 'pi = ', pi, ', % error = ', abs(100.0d0*(pi-exactpi)/exactpi)

end program piserial
