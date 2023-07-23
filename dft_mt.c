#include <stdio.h>
#include <pthread.h>
#include "performanceNow.h"
#include "readFloatFromInt16.h"
#include "dft.h"
#include "writeFloat.h"

typedef struct {
  int threadid;
  int nthread;
  int len;
  float* src;
  float* re;
  float* im;
} thread_t;

void* thread_func(void* arg) {
  thread_t* d = (thread_t*)arg;
  int id = d->threadid;
  int len = d->len;
  int tlen = len / d->nthread;
  int start = tlen * id;
  int end = tlen * (id + 1);
  if (end + tlen > len) {
    end = len;
  }
  for (int i = start; i < end; i++) {
    dft1(d->src, len, d->re, d->im, i);
  }
  return NULL;
}

int check(int nthread, float* src, size_t len, float* re, float* im) {
  double now = performanceNow();
  clock_t nowc = clock();

  pthread_t threads[nthread];
  thread_t data[nthread];
  for (int i = 0; i < nthread; i++) {
    data[i].threadid = i;
    data[i].nthread = nthread;
    data[i].len = len;
    data[i].src = src;
    data[i].re = re;
    data[i].im = im;
    pthread_create(&threads[i], NULL, thread_func, &data[i]);
  }
  for (int i = 0; i < nthread; i++) {
    pthread_join(threads[i], NULL);
  }
  double dt = performanceNow() - now;
  double dtc = (double)(clock() - nowc) / CLOCKS_PER_SEC;

  printf("%d,", nthread);
  printf("%f,", dt);
  printf("%f\n", dtc);
  return 0;
}

int main(void) {
  int benchmark = 1;

  const char* fn = "sekaideichiban.wav-r.i16.bin";
  const char* fnre = "sekaideichiban.wav-re.f32.bin";
  const char* fnim = "sekaideichiban.wav-im.f32.bin";
  
  size_t len = 0;
  float* src = readFloatFromInt16(fn, &len);
  if (!src) {
    return 1;
  }

  float* re = (float*)malloc(len * sizeof(float));
  float* im = (float*)malloc(len * sizeof(float));

  printf("nthread,time,cputime\n");
  if (benchmark) {
    for (int i = 1; i <= 20; i++) {
      check(i, src, len, re, im);
    }
  } else {
    check(6, src, len, re, im); // for M1 Pro
  }

  writeFloat(fnre, re, len);
  writeFloat(fnim, im, len);

  free(re);
  free(im);
  free(src);

  return 0;
}
