#include "writeData.h"

int writeDouble(const char* fn, const double* data, size_t len) {
  return writeData(fn, (const char*)data, len * sizeof(double));
}
