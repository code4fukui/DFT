#include <stdio.h>
#include <stdlib.h>
#include "readFloatFromInt16.h"
#include "dft.h"
#include "writeFloat.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include "stopwatch.h"

/*
dim3 gridDim x, y
dim3 blockDim x, y, z
dim3 blockIdx
dim3 threadIdx
*/
__global__ void vector_dft(float* src, size_t len, float* re, float* im) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= len) {
    return;
  }
  float re1 = 0.0f;
  float im1 = 0.0f;
  float dth = (2.0f * (float)M_PI) * i / len;
  float th = 0.0f;
  for (int j = 0; j < len; j++) {
    float d = src[j];
    re1 += d * cosf(th);
    im1 -= d * sinf(th);
    th += dth;
  }
  re[i] = re1;
  im[i] = im1;
}

int check(int nthread, float* src, size_t len, float* re, float* im) {
  clock_t nowc = clock();
  stopwatch_start();

  // Allocate memory
  float* d_src;
  float* d_re;
  float* d_im;
  cudaMalloc((void**)&d_src, sizeof(float) * len);
  cudaMalloc((void**)&d_re, sizeof(float) * len);
  cudaMalloc((void**)&d_im, sizeof(float) * len);

  cudaMemcpy(d_src, src, sizeof(float) * len, cudaMemcpyHostToDevice);

  int nblock = len / nthread + (len % nthread == 0 ? 0 : 1);
  vector_dft<<<nblock, nthread>>>(d_src, len, d_re, d_im);
   
  cudaMemcpy(re, d_re, sizeof(float) * len, cudaMemcpyDeviceToHost);
  cudaMemcpy(im, d_im, sizeof(float) * len, cudaMemcpyDeviceToHost);

  // Deallocate device memory
  cudaFree(d_src);
  cudaFree(d_re);
  cudaFree(d_im);

  float dt =   stopwatch_stop();
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
  const char* fnre = "sekaideichiban.wav-re.f32.bin";
  const char* fnim = "sekaideichiban.wav-im.f32.bin";
  
  size_t len = 0;
  float* src = readFloatFromInt16(fn, &len);
  if (!src) {
    return 1;
  }
  printf("len: %zu\n", len);

  float* re = (float*)malloc(len * sizeof(float));
  float* im = (float*)malloc(len * sizeof(float));

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
  writeFloat(fnre, re, len);
  writeFloat(fnim, im, len);

  free(re);
  free(im);
  free(src);

  return 0;
}
