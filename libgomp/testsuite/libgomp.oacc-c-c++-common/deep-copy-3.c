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

#pragma omp target data map(to:v.d[:n])
#pragma acc data copyin (v.d[:n])
  {
#pragma omp target teams distribute parallel for map(tofrom:v.a, v.b[:n])
#pragma acc parallel loop copy(v.a, v.b[:n])
  for (i = 0; i < n; i++)
    {
      v.b[i] = v.a + v.d[i];
    }
  }

  for (i = 0; i < 10; i++)
    printf ("%d: %d\n", i, v.b[i]);

  return 0;
}
