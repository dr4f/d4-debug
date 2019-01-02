#include "row_info.h"
#include "dr4_types.h"
#include <string.h>

#define HANDLE_UNKNOWN_SIZER(row) \
               fprintf(stderr, "Internal Error: Got unrecognized size type %u for row\n", row->size_type); \
               exit(3)

#define ROW_SIZE_REF(row, type) (((type*)row)->size)

#define ROW_PRINT_PREF printf("(row)-> ")

void row_info_init_row(dr4_row_t* row)
{
	switch(row->size_type)
	{
		case DR4_SIZER_8:
		     ((dr4_row_8b_t*)row)->size = DR4_ROW_INFO_DEFAULT;
		     ((dr4_row_8b_t*)row)->content = malloc(DR4_ROW_INFO_DEFAULT);
		     break;
		case DR4_SIZER_16:
		     ((dr4_row_16b_t*)row)->size = DR4_ROW_INFO_DEFAULT;
		     ((dr4_row_16b_t*)row)->content = malloc(DR4_ROW_INFO_DEFAULT);
		     break;
		case DR4_SIZER_32:
		     ((dr4_row_32b_t*)row)->size = DR4_ROW_INFO_DEFAULT;
		     ((dr4_row_32b_t*)row)->content = malloc(DR4_ROW_INFO_DEFAULT);
		     break;
		default:
		     HANDLE_UNKNOWN_SIZER(row);
	}
}

void row_info_free_row(dr4_row_t* row)
{
	switch(row->size_type)
	{
		case DR4_SIZER_8:
		     free(((dr4_row_8b_t*)row)->content);
		     break;
		case DR4_SIZER_16:
		     free(((dr4_row_16b_t*)row)->content);
		     break;
		case DR4_SIZER_32:
		     free(((dr4_row_32b_t*)row)->content);
		     break;
		default:
		    HANDLE_UNKNOWN_SIZER(row);
	}
}

void row_info_expand_row(dr4_row_t* row, size_t new_size)
{
	printf("$--Expanding Row at %p to new size %lu--$\n", row, new_size);
	switch(row->size_type)
	{
		case DR4_SIZER_8:
		     ((dr4_row_8b_t*)row)->size = (unsigned char)new_size;
		     ((dr4_row_8b_t*)row)->content = realloc(((dr4_row_8b_t*)row)->content, new_size);
		     break;
		case DR4_SIZER_16:
		     ((dr4_row_16b_t*)row)->size = (uint16_t)new_size;
		     ((dr4_row_16b_t*)row)->content = realloc(((dr4_row_16b_t*)row)->content, new_size);
		     break;
		case DR4_SIZER_32:
		     ((dr4_row_32b_t*)row)->size = (uint32_t)new_size;
		     ((dr4_row_32b_t*)row)->content = realloc(((dr4_row_32b_t*)row)->content, new_size);
		     break;
		default:
		   HANDLE_UNKNOWN_SIZER(row);
	}
}

int row_info_read_row(dr4_row_t* row, FILE* fp)
{
	unsigned long size_read = 0;
	size_t size_type_of_row = 0;
	void* row_buffer;
	switch(row->size_type)
	{
		case DR4_SIZER_8:
		    size_type_of_row = 1;
		    row_buffer = ((dr4_row_8b_t*)row)->content;
		    break;
		case DR4_SIZER_16:
		    size_type_of_row = sizeof(uint16_t);
		    row_buffer = ((dr4_row_16b_t*)row)->content;
		    break;
		case DR4_SIZER_32:
		    size_type_of_row = sizeof(uint32_t);
		    row_buffer = ((dr4_row_32b_t*)row)->content;
		    break;
		default:
		   HANDLE_UNKNOWN_SIZER(row);
	}
	(void) fread(&size_read, size_type_of_row, 1, fp);
	if(size_read == 0)
	{
		// End of document is reached, 0000 padding is found.
		puts("End of dr4 document reached, found sequence \\x00\\x00\\x00\\x00");
		return 0;
	}
	printf("---Reading row with size: %lu---\n", size_read);
	switch(row->size_type)
	{
		case DR4_SIZER_8:
		    if(size_read > ROW_SIZE_REF(row, dr4_row_8b_t)) 
		    	 row_info_expand_row(row, size_read);
		    ((dr4_row_8b_t*)row)->size = (unsigned char)size_read;
		    fread(row_buffer, 1, size_read - 1, fp);
		    break;
		case DR4_SIZER_16:
		    if(size_read > ROW_SIZE_REF(row, dr4_row_16b_t)) 
		    	row_info_expand_row(row, size_read); 
		    ((dr4_row_16b_t*)row)->size = (uint16_t)size_read;
		    fread(row_buffer, 1, size_read - sizeof(uint16_t), fp);
		    break;
		case DR4_SIZER_32:
		    if(size_read > ROW_SIZE_REF(row, dr4_row_32b_t)) 
		    	 row_info_expand_row(row, size_read); 
		    ((dr4_row_32b_t*)row)->size = (uint32_t)size_read;
		    fread(row_buffer, 1, size_read - sizeof(uint32_t), fp);
		    break;
		default:
		   HANDLE_UNKNOWN_SIZER(row);
	}
	return 1;
}

static int row_info_print_value(unsigned char* data)
{
	switch(*data)
	{
		case DR4_TYPE_STOP:
		    // this shouldn't be reached 
		    fprintf(stderr, "  <Offset Error: Found STOP type as data value in row offset.>");
		    return 1;
		case DR4_TYPE_NONE:
		    printf("None");
		    return 0;
		case DR4_TYPE_BOOL:
		    printf("Bool: %s", data[1] ? "true" : "false");
		    return 0;
		default:
		    fprintf(stderr, "  <Type Error: Found unknown dr4 type with mark %u>", *data);
		    return 1;
	}
}

static int row_info_report_8b(dr4_row_8b_t* row)
{
	printf("$--Making report for 8b row at %p--$\n", row);
	unsigned char* row_len;
	unsigned char* row_offsets;
	unsigned char* row_body;
	unsigned char* buf = (unsigned char*)(row->content);
	int err_total = 0;
	row_len = buf;
	row_offsets = row_len + 1;
	row_body = row_offsets + (*row_len);
	printf("$--Setup Row report, row len at: %p, row_offsets at %p, row_body at %p--$\n",
		                          row_len,
		                          row_offsets,
		                          row_body);
	if(*row_len > row->size)
	{
		++err_total;
	}
	printf("size: %u, len: %u, ", row->size, *row_len);
	printf("offsets: [");
	for(unsigned i = 0; i < *row_len; i++)
	{
		printf("%u", row_offsets[i]);
		if(i < ((*row_len) - 1)) printf(", ");
	}
	printf("], data:[");
	for(unsigned j = 0; j < *row_len; j++)
	{
		err_total += row_info_print_value(row_body + row_offsets[j]);
		if(j < ((*row_len) - 1)) printf(", ");
	}
	printf("]\n");
	return err_total;
}

static int row_info_report_16b(dr4_row_16b_t* row)
{
	uint16_t* row_len;
	uint16_t* row_offsets;
	unsigned char* row_body;
	uint16_t* buf = (uint16_t*)(row->content);
	int err_total = 0;
	row_len = buf;
	row_offsets = row_len + 1;
	row_body = (unsigned char*)row_offsets + (*row_len);
	if(*row_len > row->size)
	{
		++err_total;
	}
	printf("size: %u, len: %u, ", row->size, *row_len);
	printf("offsets: [");
	for(unsigned i = 0; i < *row_len; i++)
	{
		printf("%u", row_offsets[i]);
		if(i < ((*row_len) - 1)) printf(", ");
	}
	printf("], data:[");
	for(unsigned j = 0; j < *row_len; j++)
	{
		err_total += row_info_print_value(row_body + row_offsets[j]);
		if(j < ((*row_len) - 1)) printf(", ");
	}
	printf("]\n");
	return err_total;
}

static int row_info_report_32b(dr4_row_32b_t* row)
{
	uint32_t* row_len;
	uint32_t* row_offsets;
	unsigned char* row_body;
	uint32_t* buf = (uint32_t*)(row->content);
	int err_total = 0;
	row_len = buf;
	row_offsets = row_len + 1;
	row_body = (unsigned char*)row_offsets + (*row_len);
	if(*row_len > row->size)
	{
		++err_total;
	}
	printf("size: %u, len: %u, ", row->size, *row_len);
	printf("offsets: [");
	for(unsigned i = 0; i < *row_len; i++)
	{
		printf("%u", row_offsets[i]);
		if(i < ((*row_len) - 1)) printf(", ");
	}
	printf("], data:[");
	for(unsigned j = 0; j < *row_len; j++)
	{
		err_total += row_info_print_value(row_body + row_offsets[j]);
		if(j < ((*row_len) - 1)) printf(", ");
	}
	printf("]\n");
	return err_total;
}

void row_info_report_row(dr4_row_t* row, dr4_row_err_t* errs)
{
	ROW_PRINT_PREF;
	switch(row->size_type)
	{
		case DR4_SIZER_8:
		     puts("---- 8bit sized row found ----");
		     errs->count += row_info_report_8b((dr4_row_8b_t*)row);
		     return;
		case DR4_SIZER_16:
		     puts("---- 16bit sized row found ----");
		     errs->count += row_info_report_16b((dr4_row_16b_t*)row);
		     return;
		case DR4_SIZER_32:
		     puts("---- 32bit sized row found ----");
		     errs->count += row_info_report_32b((dr4_row_32b_t*)row);
		     return;
		default:
		  HANDLE_UNKNOWN_SIZER(row);
	}
}
