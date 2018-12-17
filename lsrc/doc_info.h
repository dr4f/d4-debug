#ifndef DR4_DOC_INFO_H
#define DR4_DOC_INFO_H

#include <stdio.h>
#include <string.h>

#ifndef DR4_VERSION_RE
#define DR4_VERSION_RE 1
#endif // DR4_VERSION_RE

#ifndef DR4_VERSION_SUB
#define DR4_VERSION_SUB 0
#endif // DR4_VERSION_SUB

#ifndef DR4_VERSION_PATCH
#define DR4_VERSION_PATCH 0
#endif // DR4_VERSION_PATCH


typedef unsigned char dr4_size_t;

typedef struct
{
	char report[256];
	char err[256];
	int has_err;
} dr4_doc_header_report_t;

typedef struct
{
	dr4_doc_header_report_t report;
	unsigned char magic[3];
	unsigned char version[3];
	dr4_size_t sizer;
	const char* path;
} dr4_doc_header_t;

extern FILE* doc_header_init(dr4_doc_header_t* head, const char* file_path);

extern int doc_header_from_file(dr4_doc_header_t* head, FILE* fp);


#endif // DR4_DOC_INFO_H
