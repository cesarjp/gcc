/* Test the output of -finform-parallelism.  */

/* { dg-additional-options "-finform-parallelism" } */

int
main ()
{
  int x, y, z;

#pragma acc parallel loop seq /* { dg-message "ACC LOOP SEQ" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang /* { dg-message "ACC LOOP GANG" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop worker /* { dg-message "ACC LOOP WORKER" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop vector /* { dg-message "ACC LOOP VECTOR" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang vector /* { dg-message "ACC LOOP GANG VECTOR" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang worker /* { dg-message "ACC LOOP GANG WORKER" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop worker vector /* { dg-message "ACC LOOP WORKER VECTOR" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang worker vector /* { dg-message "ACC LOOP GANG WORKER VECTOR" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop /* { dg-message "ACC LOOP GANG VECTOR" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop /* { dg-message "ACC LOOP GANG WORKER" } */
  for (x = 0; x < 10; x++)
#pragma acc loop /* { dg-message "ACC LOOP VECTOR" } */
    for (y = 0; y < 10; y++)
      ;

#pragma acc parallel loop gang /* { dg-message "ACC LOOP GANG" } */
  for (x = 0; x < 10; x++)
#pragma acc loop worker /* { dg-message "ACC LOOP WORKER" } */
    for (y = 0; y < 10; y++)
#pragma acc loop vector /* { dg-message "ACC LOOP VECTOR" } */
      for (z = 0; z < 10; z++)
	;

  return 0;
}
