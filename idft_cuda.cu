#include <stdio.h>
#include <stdlib.h>
#include "readFloat.h"
#include "writeInt16.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include "stopwatch.h"
#include "float2short.h"

__global__ void vector_idft(float* re, float* im, size_t len, float* dst) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i >= len) {
    return;
  }
  float re1 = 0.0f;
  for (int j = 0; j < len; j++) {
    float th = (2.0f * (float)M_PI) * i * j / len;
    re1 += re[j] * cosf(th) - im[j] * sinf(th);
  }
  dst[i] = re1 / len;
}

int check(int nthread, float* re, float* im, size_t len, float* dst) {
  clock_t nowc = clock();
  stopwatch_start();

  // Allocate memory
  float* d_re;
  float* d_im;
  float* d_dst;
  cudaMalloc((void**)&d_re, sizeof(float) * len);
  cudaMalloc((void**)&d_im, sizeof(float) * len);
  cudaMalloc((void**)&d_dst, sizeof(float) * len);

  cudaMemcpy(d_re, re, sizeof(float) * len, cudaMemcpyHostToDevice);
  cudaMemcpy(d_im, im, sizeof(float) * len, cudaMemcpyHostToDevice);

  int nblock = len / nthread + (len % nthread == 0 ? 0 : 1);
  vector_idft<<<nblock, nthread>>>(d_re, d_im, len, d_dst);
   
  cudaMemcpy(dst, d_dst, sizeof(float) * len, cudaMemcpyDeviceToHost);

  // Deallocate device memory
  cudaFree(d_re);
  cudaFree(d_im);
  cudaFree(d_dst);

  float dt = stopwatch_stop();
  double dtc = (double)(clock() - nowc) / CLOCKS_PER_SEC;

  printf("%d,", nthread);
  printf("%d,", nblock);
  printf("%f,", dt);
  printf("%f\n", dtc);
  return 0;
}

int main(void) {
  int benchmark = 0;
  printf("benchmark mode: %d\n", benchmark);
  
  const char* fnre = "sekaideichiban.wav-re.f32.bin";
  const char* fnim = "sekaideichiban.wav-im.f32.bin";
  const char* fn2 = "sekaideichiban.wav-r-idft.i16.bin";
  
  size_t len = 0;
  float* re = readFloat(fnre, &len);
  float* im = readFloat(fnim, &len);
  if (!re || !im) {
    printf("can't read src");
    return 1;
  }
  printf("len: %zu\n", len);

  float* dst = (float*)malloc(len * sizeof(float));

  printf("nthread,nblock,time,cputime\n");
  if (benchmark) {
    // https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#compute-capabilities
    // Maximum number of threads per block = 1024
    for (int i = 1024; i >= 1; i >>= 1) {
      check(i, re, im, len, dst);
    }
  } else {
    check(1024, re, im, len, dst);
  }
  /*
  for (int i = 0; i < len; i++) {
    printf("%d %f\n", i, re[i]);
  }
  */
  writeInt16(fn2, float2short(dst, len), len);

  free(re);
  free(im);
  free(dst);

  return 0;
}
