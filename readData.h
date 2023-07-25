#include "getFileSize.h"

char* readData(const char* fn, size_t* outSize) {
  long len = getFileSize(fn);
  FILE* fp = fopen(fn, "rb");
  char* bin = (char*)malloc(len);
  int off = 0;
  int remain = len;
  for (;;) {
    size_t n = fread(bin + off, 1, remain, fp);
    if (!n) {
      return NULL;
    }
    off += n;
    remain -= n;
    if (remain == 0) {
      break;
    }
  }
  fclose(fp);
  *outSize = len;
  return bin;
}
