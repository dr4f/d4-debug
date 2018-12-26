#ifndef DR4_ROW_INFO_H
#define DR4_ROW_INFO_H
/**
 * File contains functionality for reading rows from dr4 document body.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dr4_size_type.h"

/**
 * base - structuring macro that allows rows of different types to be casted under one
 * pointer type. A small polymorphic type system. any struct with this macro can be casted to and from
 * different row types.
 */
#define DR4_ROW_INFO_BASE dr4_size_t size_type;

/* Determines the default size when initializing a row
 */
#ifndef DR4_ROW_INFO_DEFAULT
#define DR4_ROW_INFO_DEFAULT 128
#endif

/**
 * The base or "parent" struct for the size-specific rows.
 */
typedef struct
{
	DR4_ROW_INFO_BASE
} dr4_row_t;

typedef struct
{
	DR4_ROW_INFO_BASE
	unsigned char size;
	void* content;
} dr4_row_8b_t;

typedef struct
{
	DR4_ROW_INFO_BASE
	uint16_t size;
	void* content;
} dr4_row_16b_t;

typedef struct
{
	DR4_ROW_INFO_BASE
	uint32_t size;
	void* content;
} dr4_row_32b_t;

/**
 * Initializes a row with the default size for it's content buffer.
 */
extern void row_info_init_row(dr4_row_t* row);
/*
 * Frees the memory buffer inside a row struct.
 */
extern void row_info_free_row(dr4_row_t* row);
/* Expands and increases the size of the row.
 */
extern void row_info_expand_row(dr4_row_t* row, size_t new_size);
/**
 * Reads a row from the file into the row struct.
 * If the end document padding is encountered (4 bytes of 0), the function returns 0.
 * otherwise, reading is successful, and returns 1.
 */
extern int row_info_read_row(dr4_row_t* row, FILE* fp);

/**
 * This struct is intended to keep track of how many errors occur while making
 * a row's report. Such errors include invalid types, invalid data to types, 
 * and invalid lengths (e.g len of row can never be zero).
 */
typedef struct
{
	int count;
} dr4_row_err_t;

extern void row_info_report_row(dr4_row_t* row, dr4_row_err_t* errs);


#endif // DR4_ROW_INFO_H
