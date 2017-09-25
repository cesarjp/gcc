/* Expect dynamic arrays to be mapped on the accelerator via
   GOMP_MAP_0LEN_ARRAY.  */

#include <stdlib.h>
#include <assert.h>

int
main ()
{
  const int n = 1000;
  int *a, *b, *c, i;

  a = (int *) malloc (sizeof (int) * n);
  b = (int *) malloc (sizeof (int) * n);
  c = (int *) malloc (sizeof (int) * n);
  
  for (i = 0; i < n; i++)
    {
      a[i] = -1;
      b[i] = i+1;
      c[i] = 2*(i+1);
    }

#pragma acc enter data copyin(a[:n], b[:n]) create(c[0:n])
#pragma acc parallel loop
  for (i = 0; i < n; ++i)
    {
      c[i] = a[i] + b[i];
    }
#pragma acc exit data copyout(c[0:n]) delete(a[0:n], b[0:n])

  for (i = 0; i < n; i++)
    assert (a[i] = 3*(i+1));
  
  free (a);
  free (b);
  free (c);

  return 0;
}
