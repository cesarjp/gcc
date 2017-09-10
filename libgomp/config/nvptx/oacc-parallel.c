#include "libgomp.h"

void
GOACC_mutex_lock (int *mutex)
{
  gomp_mutex_lock (mutex);
}

void
GOACC_mutex_unlock (int *mutex)
{
  gomp_mutex_unlock (mutex);

}

extern int Printf (const char *, ...) __asm__ ("vprintf");
int threadpool_count = 0;

void
GOACC_threadpool_init ()
{
  int ctaid = 0;
  int nctaid = 0;

  __asm__ volatile ("mov.u32 %0,%%ctaid.x;" : "=r" (ctaid));
  __asm__ volatile ("mov.u32 %0,%%nctaid.x;" : "=r" (nctaid));

  (void) __atomic_add_fetch (&threadpool_count, 1, MEMMODEL_ACQUIRE);

  Printf ("threadpool_count = %d\n", threadpool_count);

  while (threadpool_count != nctaid)
    ;

  if (ctaid == 0)
    return;

  while (threadpool_count > 0)
    ;
}

void
GOACC_threadpool_fork ()
{
  threadpool_count = 0;
  __asm__ volatile ("membar.gl;");
}

void
GOACC_threadpool_join ()
{
  return;
}
