/* Ensure that the middle end does not assign gang level parallelism
   to orphan loop containing reductions.  */

/* { dg-do compile } */
/* { dg-additional-options "-fopt-info-note-omp" } */

#pragma acc routine gang
int
f1 () /* { dg-warning "region is gang partitioned but does not contain gang partitioned code" } */
{
  int sum = 0, i;

#pragma acc loop reduction (+:sum) /* { dg-message "Detected parallelism <acc loop worker vector>" } */
  for (i = 0; i < 100; i++)
    sum++;

  return sum;
}

#pragma acc routine gang
int
f2 () /* { dg-warning "region is gang partitioned but does not contain gang partitioned code" } */
{
  int sum = 0, i, j;

#pragma acc loop reduction (+:sum) /* { dg-message "Detected parallelism <acc loop worker>" } */
  for (i = 0; i < 100; i++)
#pragma acc loop reduction (+:sum) /* { dg-message "Detected parallelism <acc loop vector>" } */
    for (j = 0; j < 100; j++)
      sum++;

  return sum;
}

#pragma acc routine gang
int
f3 () /* { dg-warning "region is gang partitioned but does not contain gang partitioned code" } */
{
  int sum = 0, i, j, k;

#pragma acc loop reduction (+:sum) /* { dg-message "Detected parallelism <acc loop worker>" } */
  for (i = 0; i < 100; i++)
#pragma acc loop reduction (+:sum) /* { dg-message "Detected parallelism <acc loop seq>" } */
    for (j = 0; j < 100; j++)
#pragma acc loop reduction (+:sum) /* { dg-message "Detected parallelism <acc loop vector>" } */
      for (k = 0; k < 100; k++)
	sum++;

  return sum;
}

/* { dg-warning "insufficient partitioning available to parallelize loop" "" { target *-*-* } 43 } */
