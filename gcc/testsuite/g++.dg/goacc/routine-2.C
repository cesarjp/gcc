/* Test invalid use of the routine directive.  */

template <typename T>
extern T one_d();
#pragma acc routine (one_d) nohost seq /* { dg-error "names a set of overloads" } */


int incr (int);
float incr (float);

#pragma acc routine (incr) seq /* { dg-error "names a set of overloads" } */


int sum (int, int);

namespace foo {
#pragma acc routine (sum) seq
  int sub (int, int);
}

#pragma acc routine (foo::sub) seq

/* It's strange to apply a routine directive to subset of overloaded
   functions, but that is permissible in OpenACC 2.x.  */

int decr (int a);

#pragma acc routine seq
float decr (float a);
