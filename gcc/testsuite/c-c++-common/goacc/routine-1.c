/* Test valid use of clauses with routine.  */

#pragma acc routine gang
void gang (void)
{
}

#pragma acc routine worker
void worker (void)
{
}

#pragma acc routine vector
void vector (void)
{
}

#pragma acc routine seq
void seq (void)
{
}

#pragma acc routine \
  nohost
void nohost (void)
{
}

#pragma acc routine \
  nohost
extern void nohost (void);

#pragma acc routine (nohost) \
  nohost

int main ()
{
#pragma acc kernels num_gangs (32) num_workers (32) vector_length (32)
  {
    gang ();
    worker ();
    vector ();
    seq ();
    nohost ();
  }

#pragma acc parallel num_gangs (32) num_workers (32) vector_length (32)
  {
    gang ();
    worker ();
    vector ();
    seq ();
    nohost ();
  }

  return 0;
}
