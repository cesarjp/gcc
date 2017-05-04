/* Test invalid usages of the if_present clause.  */

/* { dg-compile } */

#pragma acc routine gang if_present /* { dg-error "'if_present' is not valid" } */
void
t1 ()
{
  int a, b, c[10];

#pragma acc enter data copyin(a) if_present /* { dg-error "'if_present' is not valid" } */
#pragma acc exit data copyout(a) if_present /* { dg-error "'if_present' is not valid" } */

#pragma acc data copy(a) if_present /* { dg-error "'if_present' is not valid" } */
  {
  }

#pragma acc declare create(c) if_present /* { dg-error "'if_present' is not valid" } */

#pragma acc init if_present
#pragma acc shutdown if_present
}

void
t2 ()
{
  int a, b, c[10];

#pragma acc update self(a) device_type(nvidia) if_present /* { dg-error "'if_present' is not valid" } */
#pragma acc parallel
#pragma acc loop if_present /* { dg-error "'if_present' is not valid" } */
  for (b = 1; b < 10; b++)
    ;
#pragma acc end parallel

#pragma acc kernels loop if_present /* { dg-error "'if_present' is not valid" } */
  for (b = 1; b < 10; b++)
    ;

#pragma acc parallel loop if_present /* { dg-error "'if_present' is not valid" } */
    for (b = 1; b < 10; b++)
    ;
}

