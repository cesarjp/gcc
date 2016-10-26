! Test ACC UPDATE with derived types. The DEVICE clause depends on an
! accelerator being present.

! { dg-do run  { target openacc_nvidia_accel_selected } }

program derived_acc
  implicit none
  type mytype
     integer(8) :: a, b
  end type mytype
  type(mytype) :: var

  var%a = 0
  var%b = 1

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
  
  !$acc exit data delete(var)
end program derived_acc
