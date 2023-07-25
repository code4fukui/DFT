#include "readData.h"

float* readFloat(const char* fn, size_t* outSize) {
  char* bin = readData(fn, outSize);
  if (bin == NULL) {
    return NULL;
  }
  *outSize /= sizeof(float);
  return (float*)bin;
}
