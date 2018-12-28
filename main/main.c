#include <stdio.h>
#include "doc_info.h"
#include "row_info.h"




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

	// rows phase
	switch(doc.sizer)
	{
		case DR4_SIZER_8:
		     break;
		case DR4_SIZER_16:
		     break;
		case DR4_SIZER_32:
		     break;
		default:
		   fprintf(stderr, "Size Error: Got unknown sizer type: %u\n", doc.sizer);
		   return 0;
	}
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
