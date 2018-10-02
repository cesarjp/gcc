/* Test various aspects of clauses specifying compatible levels of
   parallelism with the OpenACC routine directive.  The Fortran counterpart is
   ../../gfortran.dg/goacc/routine-level-of-parallelism-2.f.  */

#pragma acc routine gang
void g_1 (void) /* { dg-warning "region is gang partitioned but does not contain gang partitioned code" } */
/* { dg-bogus "region is worker partitioned but does not contain worker partitioned code" "worker partitioned" { xfail *-*-* } .-1 } */
/* { dg-bogus "region is vector partitioned but does not contain vector partitioned code" "worker partitioned" { xfail *-*-* } .-2 } */
{
}
#pragma acc routine (g_1) gang
#pragma acc routine (g_1) gang


extern void w_1 (void);
#pragma acc routine (w_1) worker
#pragma acc routine (w_1) worker
#pragma acc routine (w_1) worker


#pragma acc routine vector
extern void v_1 (void);
#pragma acc routine (v_1) vector
#pragma acc routine (v_1) vector


/* Also test the implicit seq clause.  */

#pragma acc routine seq
extern void s_1_1 (void);
#pragma acc routine (s_1_1)
#pragma acc routine (s_1_1) seq
#pragma acc routine (s_1_1)
#pragma acc routine (s_1_1) seq

#pragma acc routine
extern void s_1_2 (void);
#pragma acc routine (s_1_2)
#pragma acc routine (s_1_2) seq
#pragma acc routine (s_1_2)
#pragma acc routine (s_1_2) seq

extern void s_2_1 (void);
#pragma acc routine (s_2_1) seq
#pragma acc routine (s_2_1)
#pragma acc routine (s_2_1) seq
#pragma acc routine (s_2_1)
#pragma acc routine (s_2_1) seq

extern void s_2_2 (void);
#pragma acc routine (s_2_2)
#pragma acc routine (s_2_2)
#pragma acc routine (s_2_2) seq
#pragma acc routine (s_2_2)
#pragma acc routine (s_2_2) seq

#pragma acc routine seq
void s_3_1 (void)
{
}
#pragma acc routine (s_3_1)
#pragma acc routine (s_3_1) seq
#pragma acc routine (s_3_1)
#pragma acc routine (s_3_1) seq

#pragma acc routine
void s_3_2 (void)
{
}
#pragma acc routine (s_3_2)
#pragma acc routine (s_3_2) seq
#pragma acc routine (s_3_2)
#pragma acc routine (s_3_2) seq
