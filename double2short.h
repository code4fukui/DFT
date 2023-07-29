short* double2short(double* data, size_t len) {
  if (!data) {
    return NULL;
  }
  short* res = (short*)malloc(len * sizeof(short));
  for (size_t i = 0; i < len; i++) {
    res[i] = (short)data[i];
  }
  free(data);
  return res;
}
