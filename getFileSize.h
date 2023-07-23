#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ERR_PRINTF_EXIT(...) do { fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); } while(0)

/**
 * @brief ファイルサイズ取得. Windows / Linux 両対応, のはず.
 * @param[in] in_fname ファイル名の文字列
 * @retval ファイルサイズ
 */
static long getFileSize(const char *in_fname) {
    FILE *fp;
    long file_size;
    struct stat stbuf;
    int fd;

    fd = open(in_fname, O_RDONLY);
    if (fd == -1)
        ERR_PRINTF_EXIT("cant open file : %s.\n", in_fname);

    fp = fdopen(fd, "rb");
    if (fp == NULL)
        ERR_PRINTF_EXIT("cant open file : %s.\n", in_fname);

    if (fstat(fd, &stbuf) == -1)
        ERR_PRINTF_EXIT("cant get file state : %s.\n", in_fname);

    file_size = stbuf.st_size;

    if (fclose(fp) != 0)
        ERR_PRINTF_EXIT("cant close file : %s.\n", in_fname);

    return file_size;
}
