float* short2float(short* data, size_t len) {
  if (!data) {
    return NULL;
  }
  float* res = (float*)malloc(len * sizeof(float));
  for (size_t i = 0; i < len; i++) {
    res[i] = (float)data[i];
  }
  free(data);
  return res;
}
