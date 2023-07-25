#include "writeData.h"

int writeInt16(const char* fn, const short* data, size_t len) {
  return writeData(fn, (const char*)data, len * sizeof(short));
}
