#include "getFileSize.h"

char* readAll(const char* fn, size_t* outSize) {
  long len = getFileSize(fn);
  FILE* fp = fopen(fn, "rb");
  char* bin = malloc(len);
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

short* readInt16(const char* fn, size_t* outSize) {
  char* bin = readAll(fn, outSize);
  if (bin == NULL) {
    return NULL;
  }
  *outSize /= sizeof(short);
  return (short*)bin;
}
