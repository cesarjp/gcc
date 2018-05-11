/* { dg-do run { target openacc_nvidia_accel_selected } } */
/* { dg-additional-options "-lcuda" } */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openacc.h>
#include <cuda.h>
#include <sys/time.h>

int
main (int argc, char **argv)
{
  CUfunction delay;
  CUmodule module;
  CUresult r;
  const int N = 2;
  int i;
  CUstream stream;
  struct timeval tv1, tv2;
  time_t t1, t2;

  acc_init (acc_device_nvidia);

  r = cuModuleLoad (&module, "subr.ptx");
  if (r != CUDA_SUCCESS)
    {
      fprintf (stderr, "cuModuleLoad failed: %d\n", r);
      abort ();
    }

  r = cuModuleGetFunction (&delay, module, "delay");
  if (r != CUDA_SUCCESS)
    {
      fprintf (stderr, "cuModuleGetFunction failed: %d\n", r);
      abort ();
    }

  gettimeofday (&tv1, NULL);

  r = cuLaunchKernel (delay, 1, 1, 1, 1, 1, 1, 0, NULL, NULL, 0);
  if (r != CUDA_SUCCESS)
    {
      fprintf (stderr, "cuLaunchKernel failed: %d\n", r);
      abort ();
    }

  r = cuCtxSynchronize ();
  if (r != CUDA_SUCCESS)
    {
      fprintf (stderr, "cuCtxSynchronize failed: %d\n", r);
      abort ();
    }

  gettimeofday (&tv2, NULL);

  t1 = ((tv2.tv_sec - tv1.tv_sec) * 1000000) + (tv2.tv_usec - tv1.tv_usec);

  r = cuStreamCreate (&stream, CU_STREAM_DEFAULT);
  if (r != CUDA_SUCCESS)
    {
      fprintf (stderr, "cuStreamCreate failed: %d\n", r);
      abort ();
    }

  if (!acc_set_cuda_stream (1, stream))
    abort ();

  stream = (CUstream) acc_get_cuda_stream (0);
  if (stream != NULL)
    abort ();

  r = cuStreamCreate (&stream, CU_STREAM_DEFAULT);
  if (r != CUDA_SUCCESS)
    {
      fprintf (stderr, "cuStreamCreate failed: %d\n", r);
      abort ();
    }

  if (!acc_set_cuda_stream (0, stream))
    abort ();

  gettimeofday (&tv1, NULL);

  for (i = 0; i < N; i++)
    {
      stream = (CUstream) acc_get_cuda_stream (i & 1);
      r = cuLaunchKernel (delay, 1, 1, 1, 1, 1, 1, 0, stream, NULL, 0);
      if (r != CUDA_SUCCESS)
	{
	  fprintf (stderr, "cuLaunchKernel failed: %d\n", r);
	  abort ();
	}
    }

  if (acc_async_test (0) != 0)
    abort ();
  
  acc_wait_async (0, 1);

  if (acc_async_test (1) != 0)
    abort ();

  acc_wait (1);

  gettimeofday (&tv2, NULL);

  if (acc_async_test (0) != 1)
    abort ();

  if (acc_async_test (1) != 1)
    abort ();

  t2 = ((tv2.tv_sec - tv1.tv_sec) * 1000000) + (tv2.tv_usec - tv1.tv_usec);

  t1 *= N;

  if (((abs (t2 - t1) / t1) * 100.0) > 1.0)
    {
      fprintf (stderr, "too long\n");
      abort ();
    }

  acc_shutdown (acc_device_nvidia);

  exit (0);
}

/* { dg-output "" } */
