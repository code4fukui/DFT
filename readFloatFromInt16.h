#include "readInt16.h"
#include "short2float.h"

float* readFloatFromInt16(const char* fn, size_t* outLen) {
  short* n = readInt16(fn, outLen);
  if (!n) {
    return NULL;
  }
  return short2float(n, *outLen);
}
