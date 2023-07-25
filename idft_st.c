#include <stdio.h>
#include <stdlib.h>
#include "dft.h"
#include "readFloat.h"
#include "writeInt16.h"
#include "performanceNow.h"
#include "float2short.h"

int main() {
  const char* fn = "sekaideichiban.wav-r-idftst.i16.bin";
  const char* fnre = "sekaideichiban.wav-re.f32.bin";
  const char* fnim = "sekaideichiban.wav-im.f32.bin";
  
  size_t len = 0;
  float* re = readFloat(fnre, &len);
  float* im = readFloat(fnim, &len);

  if (!re || !im) {
    return 1;
  }
  // DFT
  double now = performanceNow();
  float* dst = (float*)malloc(len * sizeof(float));
  idft(re, im, len, dst);
  double dt = performanceNow() - now;

  printf("time: %f\n", dt); // 44100samples, time: 14.769461
  short* dst2 = float2short(dst, len);
  writeInt16(fn, dst2, len);
  free(re);
  free(im);
  free(dst2);
  return 0;
}
