cudaEvent_t start, stop;

void stopwatch_start() {
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start);
}

float stopwatch_stop() {
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  float milliseconds = 0.0f;
  cudaEventElapsedTime(&milliseconds, start, stop);
  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  float dt = milliseconds / 1000.0f;
  return dt;
}
