#include "writeData.h"

int writeFloat(const char* fn, const float* data, size_t len) {
  return writeData(fn, (const char*)data, len * sizeof(float));
}
