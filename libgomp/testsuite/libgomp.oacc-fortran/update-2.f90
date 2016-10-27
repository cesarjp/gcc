! Test ACC UPDATE with derived types. The DEVICE clause depends on an
! accelerator being present.

! { dg-do run  { target openacc_nvidia_accel_selected } }

module dt
  integer, parameter :: n = 10
  type mytype
     integer(8) :: a, b, c(n)
     integer, allocatable :: d(:)
  end type mytype
end module dt

program derived_acc
  use dt

  implicit none
  integer i, res
  type(mytype) :: var

  var%a = 0
  var%b = 1
  var%c(:) = 10
  allocate(var%d(n))

  !$acc enter data copyin(var)

  !$acc parallel present(var) num_gangs(1) num_workers(1)
  var%a = var%b
  !$acc end parallel

  !$acc update host(var%a)

  if (var%a .ne. var%b) call abort

  var%b = 100

  !$acc update device(var%b)

  !$acc parallel present(var) num_gangs(1) num_workers(1)
  var%a = var%b
  !$acc end parallel

  !$acc update host(var%a)

  if (var%a .ne. var%b) call abort

  !$acc parallel loop present (var)
  do i = 1, n
     var%c(i) = i
  end do
  !$acc end parallel loop

  !$acc update host(var%c)

  var%a = -1

  do i = 1, n
     if (var%c(i) .ne. i) call abort
     var%c(i) = var%a
  end do

  !$acc update device(var%a)
  !$acc update device(var%c)

  res = 0

  !$acc parallel loop present(var) reduction(+:res)
  do i = 1, n
     if (var%c(i) .ne. var%a) res = res + 1
  end do

  if (res .ne. 0) call abort

  !$acc exit data delete(var)
end program derived_acc
