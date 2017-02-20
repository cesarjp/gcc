! Test the output of -finform-parallellism.

! { dg-additional-options "-finform-parallelism" }

program test
  implicit none

  integer x, y, z

  !$acc parallel loop seq ! { dg-message "ACC LOOP SEQ" }
  do x = 1, 10
  end do

  !$acc parallel loop gang ! { dg-message "ACC LOOP GANG" }
  do x = 1, 10
  end do

  !$acc parallel loop worker ! { dg-message "ACC LOOP WORKER" }
  do x = 1, 10
  end do

  !$acc parallel loop vector ! { dg-message "ACC LOOP VECTOR" }
  do x = 1, 10
  end do

  !$acc parallel loop gang vector ! { dg-message "ACC LOOP GANG VECTOR" }
  do x = 1, 10
  end do

  !$acc parallel loop gang worker ! { dg-message "ACC LOOP GANG WORKER" }
  do x = 1, 10
  end do

  !$acc parallel loop worker vector ! { dg-message "ACC LOOP WORKER VECTOR" }
  do x = 1, 10
  end do

  !$acc parallel loop gang worker vector ! { dg-message "ACC LOOP GANG WORKER VECTOR" }
  do x = 1, 10
  end do

  !$acc parallel loop ! { dg-message "ACC LOOP GANG VECTOR" }
  do x = 1, 10
  end do

  !$acc parallel loop ! { dg-message "ACC LOOP GANG WORKER" }
  do x = 1, 10
     !$acc loop ! { dg-message "ACC LOOP VECTOR" }
     do y = 1, 10
     end do
  end do

  !$acc parallel loop gang ! { dg-message "ACC LOOP GANG" }
  do x = 1, 10
     !$acc loop worker ! { dg-message "ACC LOOP WORKER" }
     do y = 1, 10
        !$acc loop vector ! { dg-message "ACC LOOP VECTOR" }
        do z = 1, 10
        end do
     end do
  end do
end program test
