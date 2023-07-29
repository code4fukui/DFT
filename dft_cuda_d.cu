#include <stdio.h>
#include <stdlib.h>
#include "readDoubleFromInt16.h"
#include "dft.h"
#include "writeDouble.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include "stopwatch.h"

/*
dim3 gridDim x, y
dim3 blockDim x, y, z
dim3 blockIdx
dim3 threadIdx
*/
__global__ void vector_dft(double* src, size_t len, double* re, double* im) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= len) {
    return;
  }
  double re1 = 0.0;
  double im1 = 0.0;
  for (int j = 0; j < len; j++) {
    double th = (2.0 * M_PI) * i * j / len;
    double d = src[j];
    re1 += d * cos(th);
    im1 -= d * sin(th);
  }
  re[i] = re1;
  im[i] = im1;
}

int check(int nthread, double* src, size_t len, double* re, double* im) {
  clock_t nowc = clock();
  stopwatch_start();

  // Allocate memory
  double* d_src;
  double* d_re;
  double* d_im;
  cudaMalloc((void**)&d_src, sizeof(double) * len);
  cudaMalloc((void**)&d_re, sizeof(double) * len);
  cudaMalloc((void**)&d_im, sizeof(double) * len);

  cudaMemcpy(d_src, src, sizeof(double) * len, cudaMemcpyHostToDevice);

  int nblock = len / nthread + (len % nthread == 0 ? 0 : 1);
  vector_dft<<<nblock, nthread>>>(d_src, len, d_re, d_im);
   
  cudaMemcpy(re, d_re, sizeof(double) * len, cudaMemcpyDeviceToHost);
  cudaMemcpy(im, d_im, sizeof(double) * len, cudaMemcpyDeviceToHost);

  // Deallocate device memory
  cudaFree(d_src);
  cudaFree(d_re);
  cudaFree(d_im);

  double dt = stopwatch_stop();
  double dtc = (double)(clock() - nowc) / CLOCKS_PER_SEC;

  printf("%d,", nthread);
  printf("%d,", nblock);
  printf("%f,", dt);
  printf("%f\n", dtc);
  return 0;
}

int main(void) {
  int benchmark = 0;

  const char* fn = "sekaideichiban.wav-r.i16.bin";
  const char* fnre = "sekaideichiban.wav-re.f64.bin";
  const char* fnim = "sekaideichiban.wav-im.f64.bin";
  
  size_t len = 0;
  double* src = readDoubleFromInt16(fn, &len);
  if (!src) {
    return 1;
  }
  printf("len: %zu\n", len);

  double* re = (double*)malloc(len * sizeof(double));
  double* im = (double*)malloc(len * sizeof(double));

  for (int i = 0; i < len; i++) {
    re[i] = i;
  }

  printf("nthread,nblock,time,cputime\n");
  if (benchmark) {
    // https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#compute-capabilities
    // Maximum number of threads per block = 1024
    for (int i = 1024; i >= 1; i >>= 1) {
      check(i, src, len, re, im);
    }
  } else {
    check(1024, src, len, re, im); // for RXT3060Ti
  }
  /*
  for (int i = 0; i < len; i++) {
    printf("%d %f\n", i, re[i]);
  }
  */
  writeDouble(fnre, re, len);
  writeDouble(fnim, im, len);

  free(re);
  free(im);
  free(src);

  return 0;
}
