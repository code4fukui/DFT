#include <stdio.h>
#include "readFloatFromInt16.h"
#include "dft.h"
#include "writeFloat.h"
#include "performanceNow.h"

int main() {
  const char* fn = "sekaideichiban.wav-r.i16.bin";
  const char* fnre = "sekaideichiban.wav-re.f32.bin";
  const char* fnim = "sekaideichiban.wav-im.f32.bin";
  
  size_t len = 0;
  float* src = readFloatFromInt16(fn, &len);
  if (!src) {
    return 1;
  }
  // DFT
  double now = performanceNow();
  float* re = (float*)malloc(len * sizeof(float));
  float* im = (float*)malloc(len * sizeof(float));
  dft(src, len, re, im);
  double dt = performanceNow() - now;
  printf("time: %f\n", dt); // 44100samples, time: 14.769461
  writeFloat(fnre, re, len);
  writeFloat(fnim, im, len);
  free(re);
  free(im);
  free(src);
  return 0;
}
