#include <assert.h>
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

#pragma acc enter data copyin (v.d[:n])

#pragma acc parallel loop copy(v.a, v.b[:n])
  for (i = 0; i < n; i++)
    {
      v.b[i] = v.d[i];
    }

#pragma acc exit data delete (v.d[:n])
  
  for (i = 0; i < 10; i++)
    assert (v.b[i] == v.d[i]);

  return 0;
}
