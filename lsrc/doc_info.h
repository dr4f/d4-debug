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

/*Typed Sizer Constants*/
static const dr4_size_t DR4_SIZER_8 = 8;
static const dr4_size_t DR4_SIZER_16 = 16;
static const dr4_size_t DR4_SIZER_32 = 32;

typedef struct
{
	char report[1024];
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
/**
 * Extern alias function to validate a magic sequence.
 */
extern int doc_header_check_magic(dr4_doc_header_t* head);
/**
 * Extern alias function to validate a dr4 version.
 */
extern int doc_header_check_version(dr4_doc_header_t* head);
/**
 * External alias function to check sizer.
 */
extern int doc_header_check_sizer(dr4_doc_header_t* head);
/**
 * Opens the file for a header and writes the file path to
 * the header struct.
 */
extern FILE* doc_header_init(dr4_doc_header_t* head, const char* file_path);
/**
 * Initializes a doc header struct without opening a file, used mainly for testing.
 */
extern void doc_header_init_nof(dr4_doc_header_t* head);
/**
 * Extracts 8 bytes from file to find header data. Returns 0 if file cannot be opened,
 * or error in reading exactly 8 bytes.
 */
extern int doc_header_from_file(dr4_doc_header_t* head, FILE* fp);

extern void doc_header_make_report(dr4_doc_header_t* head);


#endif // DR4_DOC_INFO_H
