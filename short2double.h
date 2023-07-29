double* short2double(short* data, size_t len) {
  if (!data) {
    return NULL;
  }
  double* res = (double*)malloc(len * sizeof(double));
  for (size_t i = 0; i < len; i++) {
    res[i] = (double)data[i];
  }
  free(data);
  return res;
}
