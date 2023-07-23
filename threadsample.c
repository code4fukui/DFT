// thread sample
// original src: https://daeudaeu.com/time_clock/

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "performanceNow.h"

#define N 200000

typedef struct {
  int threadid;
  int nthread;
  int sum;
} thread_t;

void* thread_func(void* arg) {
  thread_t* d = (thread_t*)arg;
  // 担当領域の計算
  int id = d->threadid;
  int len = N / d->nthread;
  int start = len * id;
  int end = len * (id + 1);
  if (end + len > N) {
    end = N;
  }
  // 担当処理
  int sum = 0;
  for (int i = start; i < end; i++) {
    for (int j = 0; j < N; j++) {
      sum += N * i + j;
    }
  }
  d->sum = sum;
  return NULL;
}

int check(int nthread) {
  int sum = 0;
  
  double start_time = performanceNow();
  clock_t start_clock = clock();

  pthread_t threads[nthread];
  thread_t data[nthread];
  for (int i = 0; i < nthread; i++) {
    data[i].threadid = i;
    data[i].nthread = nthread;
    data[i].sum = 0;
    pthread_create(&threads[i], NULL, thread_func, &data[i]);
  }
  for (int i = 0; i < nthread; i++) {
    pthread_join(threads[i], NULL);
  }
  for (int i = 0; i < nthread; i++) {
    sum += data[i].sum;
  }

  double end_time = performanceNow();
  clock_t end_clock = clock();

  printf("%d,", nthread);
  printf("%f,", end_time - start_time);
  printf("%f,", (double)(end_clock - start_clock) / CLOCKS_PER_SEC);
  printf("%d\n", sum);
  return 0;
}

int main(void) {
  printf("nthread,time,clock,sum\n");
  for (int i = 1; i <= 32; i++) {
    check(i);
  }
  return 0;
}
