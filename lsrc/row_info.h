#ifndef DR4_ROW_INFO_H
#define DR4_ROW_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * File contains functionality for reading rows from dr4 document body.
 */


#define ROW_STRUCT_DEFINER(bname, size_type) \
            typedef struct {    \
                  size_type size;   \
                  size_type len;    \
                  size_type offsets*; \
            } bname##size_type

#endif // DR4_ROW_INFO_H
