! Check warning on orphan reductions.

! { dg-do compile }

subroutine s
  implicit none
  !$acc routine gang
  integer i, sum

  !$acc loop gang worker vector reduction(+:sum) ! { dg-warning "gang reduction on an orphan loop" }
  do i = 1, 100
     sum = sum + 1
  end do
end subroutine s

integer function f ()
  implicit none
  !$acc routine gang
  integer i, sum

  !$acc loop gang worker vector reduction(+:sum) ! { dg-warning "gang reduction on an orphan loop" }
  do i = 1, 100
     sum = sum + 1
  end do
end function f

module m
  contains
  subroutine s
    implicit none
    !$acc routine gang
    integer i, sum

    !$acc loop gang worker vector reduction(+:sum) ! { dg-warning "gang reduction on an orphan loop" }
    do i = 1, 100
       sum = sum + 1
    end do
  end subroutine s

  integer function f ()
    implicit none
    !$acc routine gang
    integer i, sum

    !$acc loop gang worker vector reduction(+:sum) ! { dg-warning "gang reduction on an orphan loop" }
    do i = 1, 100
       sum = sum + 1
    end do
  end function f
end module m
