#include <sys/time.h> // gettimeofday()

double performanceNow() {
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  double now = (double)tv.tv_sec + (double)tv.tv_usec * 1.0e-6;
  return now;
}
