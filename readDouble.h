#include "readData.h"

double* readDouble(const char* fn, size_t* outSize) {
  char* bin = readData(fn, outSize);
  if (bin == NULL) {
    return NULL;
  }
  *outSize /= sizeof(double);
  return (double*)bin;
}
