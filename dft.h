#include <math.h>

#ifndef __CUDACC__
#define __device__
#endif

void dft(float* src, size_t len, float* re, float* im) {
  for (int i = 0; i < len; i++) {
    float re1 = 0.0f;
    float im1 = 0.0f;
    for (int j = 0; j < len; j++) {
      float th = (2.0f * (float)M_PI) * i * j / len;
      float d = src[j];
      re1 += d * cosf(th);
      im1 -= d * sinf(th);
    }
    re[i] = re1;
    im[i] = im1;
  }
  /*
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
  */
}

void idft(float* re, float* im, size_t len, float* dst) {
  for (int i = 0; i < len; i++) {
    float re1 = 0.0f;
    for (int j = 0; j < len; j++) {
      float th = (2.0f * (float)M_PI) * i * j / len;
      re1 += re[j] * cosf(th) - im[j] * sinf(th);
      //im1 += re[j] * Math.sin(th) + im[j] * Math.cos(th);
    }
    dst[i] = re1 / len;
    //im2[i] = im1 / len;
  }

  /*
  for (int i = 0; i < len; i++) {
    float re1 = 0.0f;
    float dth = (2.0f * (float)M_PI) * i / len;
    float th = 0.0f;
    for (int j = 0; j < len; j++) {
      re1 += re[j] * cosf(th) - im[j] * sinf(th);
      //im1 += re[j] * Math.sin(th) + im[j] * Math.cos(th);
      th += dth;
    }
    dst[i] = re1 / len;
    //im2[i] = im1 / len;
  }
  */

  /*
  for (int i = 0; i < len; i++) {
    float re1 = 0.0f;
    float th = 0.0f;
    float dth = (2.0f * (float)M_PI) * i / len;
    for (int j = 0; j < len; j++) {
      re1 += re[j] * cosf(th) - im[j] * sinf(th);
      th += dth;
    }
    dst[i] = re1 / len;
  }
  */
}

__device__ void dft1(float* src, size_t len, float* re, float* im, int i) {
  float re1 = 0.0f;
  float im1 = 0.0f;
  for (int j = 0; j < len; j++) {
    float th = (2.0f * (float)M_PI) * i * j/ len;
    float d = src[j];
    re1 += d * cosf(th);
    im1 -= d * sinf(th);
  }
  re[i] = re1;
  im[i] = im1;
  /*
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
  */
}
