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
