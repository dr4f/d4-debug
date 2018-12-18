#include "io_test_help.h"

/* If no directory is defined, the working directory is used.
 */
#ifdef DR4_DEBUG_TDIR
    static char IO_TEST_PATH_BIN[IO_TEST_PATH_SZ] = DR4_DEBUG_TDIR;
#else
    static char IO_TEST_PATH_BIN[IO_TEST_PATH_SZ];
#endif

const char* io_test_get_path(void)
{
	return IO_TEST_PATH_BIN;
}

void io_test_set_path(const char* file_name)
{
	(void) strncat(IO_TEST_PATH_BIN, file_name, IO_TEST_PATH_SZ);
}

void io_test_remove_path(void)
{
	remove(IO_TEST_PATH_BIN);
}

int io_test_real_dump(void* data, size_t n)
{
	FILE* fp;
	fp = fopen(IO_TEST_PATH_BIN, "wb");
	if(fp == NULL) return 0;
	fwrite(data, n, 1, fp);
	fclose(fp);
	return 1;
}

FILE* io_test_real_open(void)
{
	return fopen(IO_TEST_PATH_BIN, "rb");
}

FILE* io_test_dump_fake(void* data, size_t n)
{
	FILE* fp = tmpfile();
	fwrite(data, n, 1, fp);
	rewind(fp);
	return fp;
}

