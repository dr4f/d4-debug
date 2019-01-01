#include <stdio.h>
#include "doc_info.h"
#include "row_info.h"

/* Function actually responsible for executing print calls
 * and checking for termination.
 */
static void print_rows_info(dr4_row_t* row, FILE* fp)
{
	dr4_row_err_t row_err;
	unsigned row_count;
	int row_continue;
	row_continue = 1;
	row_err.count = 0;
	row_count = 0;
	while(row_continue)
	{
		row_continue = row_info_read_row(row, fp);
		if(!row_continue) break;
		row_info_report_row(row, &row_err);
		++row_count;
	}
	printf("----The document counted %d row errrors----\n", row_err.count);
	printf("----The document counted %u rows-----------\n", row_count);
}


/**
 * Function that handles high level execution of debug and info of
 * dr4 doc
 */
static int print_file_info(const char* file_path)
{
	// Header phase
	dr4_doc_header_t doc;
	FILE* fp;
    dr4_row_8b_t row8;
    dr4_row_16b_t row16;
    dr4_row_32b_t row32;
    dr4_row_t* used_row;
	fp = doc_header_init(&doc, file_path);
	if(fp == NULL)
	{
		fprintf(stderr, "FAILED: %s", doc.report.err);
		return 0;
	}
	if(!doc_header_from_file(&doc,fp))
	{
		fprintf(stderr, "FAILED: %s", doc.report.err);
		return 0;
	}
	doc_header_make_report(&doc);
	// prints the actual header report.
	printf("%s", doc.report.report);
	// rows phase
	switch(doc.sizer)
	{
		case DR4_SIZER_8:
		     used_row = (dr4_row_t*)&row8;
		     break;
		case DR4_SIZER_16:
		     used_row = (dr4_row_t*)&row16;
		     break;
		case DR4_SIZER_32:
		     used_row = (dr4_row_t*)&row32;
		     break;
		default:
		   fprintf(stderr, "Size Error: Got unknown sizer type: %u\n", doc.sizer);
		   return 0;
	}
	used_row->size_type = doc.sizer;
	row_info_init_row(used_row);
	print_rows_info(used_row, fp);
	row_info_free_row(used_row);
	return 1;
}

int main(int argc, char const *argv[])
{
	puts("____dr4_debug_____");

	if(argc == 2)
	{
		if(!print_file_info(argv[1])) {
			fprintf(stderr, "Debug report of file at %s not successful.\n", argv[1]);
			return 1;
		}
	} else {
		fprintf(stderr, "Arg Error: Expected 1 command line agrument, got %d\n", argc - 1);
		return 1;
	}
	return 0;
}
