#include <stdio.h>
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
  struct dc v = { .a = malloc (sizeof (int) * n), .b = NULL,
		  .c = malloc (sizeof (int) * n)};
  int *a = (int *) malloc (sizeof (int) * n);
  
  for (i = 0; i < n; i++)
    v.a[i] = i+1;

#pragma acc enter data copyin(a[:n]) create(v)
  v.b = a;

#pragma acc enter data attach(v.b)
  
#pragma acc parallel loop copyin(v.a[:n]) present(v.b)
  for (i = 0; i < n; i++)
    v.b[i] = v.a[i];

#pragma acc parallel loop present(v.b) copyout(v.c[:n])
  for (i = 0; i < n; i++)
    v.c[i] = v.b[i];  

#pragma acc exit data detach(v.b)
  
#pragma acc exit data copyout(a[:n])

  for (i = 0; i < 10; i++)
    printf ("%d: %d %d %d\n", i, v.a[i], v.b[i], v.c[i]);

  free (v.a);
  free (v.b);
  free (v.c);
  
  return 0;
}
