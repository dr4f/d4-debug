#include "doc_info.h"

static inline int 
_doc_header_check_magic(dr4_doc_header_t* head)
{
	return head->magic[0] == 83 &&
	       head->magic[1] == 94 &&
	       head->magic[2] == 121;
}

static inline int 
_doc_header_check_version(dr4_doc_header_t* head)
{
	return head->version[0] == DR4_VERSION_RE &&
	       head->version[1] == DR4_VERSION_SUB &&
	       head->version[2] == DR4_VERSION_PATCH;	
}

extern int doc_header_check_magic(dr4_doc_header_t* head)
{
	return _doc_header_check_magic(head);
}

extern int doc_header_check_version(dr4_doc_header_t* head)
{
	return _doc_header_check_version(head);
}

extern FILE* doc_header_init(dr4_doc_header_t* head, const char* file_path)
{
	FILE* fp;
	head->path = file_path;
	fp = fopen(file_path, "rb");
	if(fp == NULL)
	{
		head->report.has_err = 1;
		sprintf(head->report.err, "File Error: Cannot open file at '%s'\n", file_path);
		return NULL;
	}
	memset(&(head->report), 0, sizeof(dr4_doc_header_report_t));
	return fp;
}

int doc_header_from_file(dr4_doc_header_t* head, FILE* fp)
{
	unsigned char read_data[8];
	rewind(fp);
	if(fread(read_data, 1, 8, fp) != 8)
	{
		head->report.has_err = 1;
		sprintf(head->report.err, "Read Error: Failed to read document header at '%s'\n.", head->path);
		return 0;
	}
	// first is always magic sequence
	head->magic[0] = read_data[0];
	head->magic[1] = read_data[1];
	head->magic[2] = read_data[2];

	head->version[0] = read_data[3];
	head->version[1] = read_data[4];
	head->version[2] = read_data[5];
	head->sizer = read_data[6];
	return 1;
}

extern void doc_header_make_report(dr4_doc_header_t* head)
{
	
}
