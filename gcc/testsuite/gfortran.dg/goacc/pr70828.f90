! Ensure that pointer mappings are preserved in nested parallel
! constructs.

! { dg-additional-options "-fdump-tree-gimple" }

program test
  integer, parameter :: n = 100
  integer i, data(n)

  data(:) = 0

  !$acc data copy(data(5:n-10))
  !$acc parallel loop
  do i = 10, n - 10
     data(i) = i
  end do
  !$acc end parallel loop
  !$acc end data
end program test

! { dg-final { scan-tree-dump-times "omp target oacc_data map.tofrom:MEM..c_char .._6. .len: _5.. map.alloc:data .pointer assign, bias: _10.." 1 "gimple" } }
! { dg-final { scan-tree-dump-times "omp target oacc_parallel map.alloc:data .pointer assign, bias: _10.." 1 "gimple" } }
