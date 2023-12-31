#if 0

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

size_t getFileSize(const char* in_fname) { // ret 0 if err
  int fd = open(in_fname, O_RDONLY);
  if (fd == -1) {
    return 0; // can't open
  }
  FILE* fp = fdopen(fd, "rb");
  if (fp == NULL) {
    return 0; // can't open
  }
  struct stat stbuf;
  if (fstat(fd, &stbuf) == -1) {
    return 0; // cat't get fstat
  }
  size_t file_size = stbuf.st_size;
  if (fclose(fp) != 0) {
    return 0; // can't close
  }
  return file_size;
}

#else

#include <stdio.h>

size_t getFileSize(const char* fn) { // ret 0 if err
  FILE *fp = fopen(fn, "rb");
  if (!fp) {
    return 0;
  }
  fseek(fp, 0, SEEK_END);
  long filesize = ftell(fp);
  fclose(fp);
  return filesize;
}

#endif

