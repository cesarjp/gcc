/* Test orphan reductions.  */

/* { dg-do compile } */

#include <stdio.h>
#include <assert.h>

#pragma acc routine seq
int
seq_reduction (int n)
{
  int i, sum = 0;
#pragma acc loop seq reduction(+:sum)
  for (i = 0; i < n; i++)
    sum = sum + 1;
  
  return sum;
}

#pragma acc routine worker
int
worker_reduction (int n)
{
  int i, sum = 0;
#pragma acc loop worker reduction(+:sum)
  for (i = 0; i < n; i++)
    sum = sum + 3;
  
  return sum;
}

#pragma acc routine vector
int
vector_reduction (int n)
{
  int i, sum = 0;
#pragma acc loop vector reduction(+:sum)
  for (i = 0; i < n; i++)
    sum = sum + 4;
  
  return sum;
}

#pragma acc routine gang
int
gang_reduction (int n)
{
  int i, sum = 0;
#pragma acc loop gang reduction(+:sum) /* { dg-error "gang reduction on an orphan loop" } */
  for (i = 0; i < n; i++)
    sum = sum + 2;
  
  return sum;
}
