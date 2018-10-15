
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  struct foo {
    int *a, *b, c, d, *e;
  } s;

  s.a = malloc (16 * sizeof (int));
  s.b = malloc (16 * sizeof (int));
  s.e = malloc (16 * sizeof (int)); 

  //printf ("s.a = %p\n", s.a);
  
  #pragma acc data copy(s) 
  {
    #pragma acc data copy(s.a[0:10]) 
    {
      #pragma acc parallel loop attach(s.a)
      for (int i = 0; i < 10; i++)
        s.a[i] = i;
    } 
  }

  //printf ("s.a = %p\n", s.a);

  for (int i = 0; i < 10; i++)
    printf ("%u: %d\n", i, s.a[i]); 

  return 0;
}
