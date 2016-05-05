void
fun (float (&fp)[100])
{
  float *dptr = &fp[50];

#pragma omp target data map(tofrom:fp[0:2], fp[0:2]) /* { dg-error "'fp' appears more than once in data clauses" } */
  ;
}

template<typename T>
void
fun (T (&fp)[100])
{
  T *dptr = &fp[50];

#pragma omp target data map(tofrom:fp[0:2], fp[0:2]) /* { dg-error "'fp' appears more than once in map clauses" } */
  ;
}
