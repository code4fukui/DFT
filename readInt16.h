#include "readData.h"

short* readInt16(const char* fn, size_t* outSize) {
  char* bin = readData(fn, outSize);
  if (bin == NULL) {
    return NULL;
  }
  *outSize /= sizeof(short);
  return (short*)bin;
}
