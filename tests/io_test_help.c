#include "io_test_help.h"

/* If no directory is defined, the working directory is used.
 */
#ifdef DR4_DEBUG_TDIR
    static char IO_TEST_PATH_BIN[1024] = DR4_DEBUG_TDIR;
#else
    static char IO_TEST_PATH_BIN[1024];
#endif

