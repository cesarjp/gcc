/* { dg-do compile } */
/* { dg-options "-O2 -misa=sm_35" } */

int
main()
{
  unsigned long long a = ~0;
  unsigned b = 0xa;

  __atomic_fetch_and (&a, b, 0);

  return a;
}

/* { dg-final { scan-assembler-times "atom.b64.and" 1 } } */
