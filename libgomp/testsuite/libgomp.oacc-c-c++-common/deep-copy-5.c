#include <assert.h>
#include <stdlib.h>

struct dc
{
  int *a;
  int *b;
  int *c;
};

int
main ()
{
  int n = 100, i;
  struct dc v = { .a = (int *) malloc (sizeof (int) * n), .b = NULL,
		  .c = (int *) malloc (sizeof (int) * n)};
  int *a = (int *) malloc (sizeof (int) * n);
  
  for (i = 0; i < n; i++)
    v.a[i] = i+1;

#pragma acc enter data copyin (a[:n])
  v.b = a;

#pragma acc parallel loop copyin(v.a[:n]) attach(v.b)
  for (i = 0; i < n; i++)
    v.b[i] = v.a[i];

#pragma acc parallel loop attach(v.b) copyout (v.c[:n])
  for (i = 0; i < n; i++)
    v.c[i] = v.b[i];  

#pragma acc exit data delete (a[:n])

  for (i = 0; i < 10; i++)
    assert (v.a[i] == v.c[i]);

  free (v.a);
  free (v.b);
  free (v.c);
  
  return 0;
}
