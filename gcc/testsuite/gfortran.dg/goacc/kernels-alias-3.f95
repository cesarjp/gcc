! { dg-additional-options "-O2" }
! { dg-additional-options "-foffload-alias=all" }
! { dg-additional-options "-fdump-tree-ealias-all" }

program main
  implicit none
  integer, target  :: a
  integer, pointer :: ptr
  ptr => a

  !$acc kernels pcopyin (a, ptr)
  a = 0
  ptr = 1
  !$acc end kernels

end program main

! Only the omp_data_i related loads should be annotated with cliques.
! { dg-final { scan-tree-dump-times "clique 1 base 1" 2 "ealias" } }
! The following FAILs since/needs to be updated for the "Partially enable
! GOMP_MAP_FIRSTPRIVATE_POINTER in gfortran" changes.
! { dg-final { scan-tree-dump-times "(?n)clique 1 base 0" 3 "ealias" { xfail *-*-* } } }
