#ifndef IO_TEST_HELP_H
#define IO_TEST_HELP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * The max size of a test file path. 
 */
#define IO_TEST_PATH_SZ 1024
/**
 * Contains methods that help facilitate file dumping and writing
 * to specific paths in C.
 */

/* Get the current full path of the test file,
 * which has the testing dir prepended to it.
 */
extern const char* io_test_get_path(void);

/* Given the testing dir, append a file name with a '/' sep
 * to the test file path.
 */
extern void io_test_set_path(const char* file_name);
/*
 * Removes file in testing dir.
 */
extern void io_test_remove_path(void);
/*
 * Dumps data into a real file in the testing dir.
 */
extern int io_test_real_dump(void* data, size_t n);

/* 
 * Opens the file at path IO_TEST_PATH_BIN
 */
extern FILE* io_test_real_open(void);
/*
 * Instead of opening the io_test_path_bin file, this uses tmpfile() to create
 * a fake file pointer, only usable for testing purposes. It also dumps data into
 * the tmpfile and rewinds.
 */
extern FILE* io_test_dump_fake(void* data, size_t n);
/* Helper function to assert the outputs of reporting or string writing functions
 */
extern const char* io_test_find_subs(const char* string, const char* substring);

#endif // IO_TEST_HELPERS_H
