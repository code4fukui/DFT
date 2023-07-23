#include <math.h>

void dft(float* src, size_t len, float* re, float* im) {
  for (int i = 0; i < len; i++) {
    float re1 = 0.0f;
    float im1 = 0.0f;
    float dth = (2.0f * (float)M_PI) * i / len;
    float th = 0.0f;
    for (int j = 0; j < len; j++) {
      float d = src[j];
      re1 += d * cosf(th);
      im1 -= d * sinf(th);
      th += dth;
    }
    re[i] = re1;
    im[i] = im1;
  }
}

void dft1(float* src, size_t len, float* re, float* im, int i) {
  float re1 = 0.0f;
  float im1 = 0.0f;
  float dth = (2.0f * (float)M_PI) * i / len;
  float th = 0.0f;
  for (int j = 0; j < len; j++) {
    float d = src[j];
    re1 += d * cosf(th);
    im1 -= d * sinf(th);
    th += dth;
  }
  re[i] = re1;
  im[i] = im1;
}
