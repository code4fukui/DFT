int writeData(const char* fn, const char* bin, size_t len) {
  FILE* fp = fopen(fn, "wb");
  int off = 0;
  int remain = len;
  for (;;) {
    size_t n = fwrite(bin + off, 1, remain, fp);
    if (!n) {
      return 0;
    }
    off += n;
    remain -= n;
    if (remain == 0) {
      break;
    }
  }
  fclose(fp);
  return 1;
}
