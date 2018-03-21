/* Exercise different vector_lengths.  */

#include <assert.h>

#define N 10000

#define test1(pragma) #pragma

#define test(vl) do {			\
    _Pragma(test1(acc parallel loop vector_length(vl)))				\
  for (i = 0; i < N; i++)			\
    a[i] = (vl);				\
  for (i = 0; i < N; i++)			\
    assert (a[i] == (vl));			\
  } while (0) 
 
int
main ()
{
  int a[N], i;

#pragma acc parallel loop
  for (i = 0; i < N; i++)
    a[i] = 1;

  for (i = 0; i < N; i++)
    assert (a[i] == 1);

  test(32);
  test(64);
  test(96);
  test(128);
  test(256);
  test(512);
  
  return 0;
}
