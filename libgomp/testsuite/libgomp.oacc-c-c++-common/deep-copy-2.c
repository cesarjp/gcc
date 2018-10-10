#include <stdio.h>
#include <stdlib.h>

struct dc
{
  int a;
  int *b;
  int c;
  int *d;
};

int
main ()
{
  int n = 100, i;
  struct dc v = { .a = 3, .b = (int *) malloc (sizeof (int) * n),
		  .d = (int *) malloc (sizeof (int) * n) };

  for (i = 0; i < 100; i++)
    v.d[i] = 20;

  printf ("host: v.a = %p, v.b = %p, v.d = %p\n", &v.a, &v.b, &v.d);

//#pragma omp target data map(to:v)
#pragma omp target data map(to:v.d[:n])
#pragma acc data copy (v.d[:n])
  {
#pragma omp target teams distribute parallel for map(tofrom:v.a, v.b[:n])
#pragma acc parallel copy(v.a, v.b[:n])
    printf ("device: v.a = %p, v.b = %p, v.d = %p\n", &v.a, &v.b, &v.d);
    v.d[0] = 1000;
  }

  printf ("%d\n", v.d[0]);
  
//  for (i = 0; i < 10; i++)
//    printf ("%d: %d\n", i, v.b[i]);

  return 0;
}
