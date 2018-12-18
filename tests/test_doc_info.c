#include "test_failures.h"
#include "io_test_help.h"
#include "doc_info.h"




void test_doc_header_check_magic(void)
{
	dr4_doc_header_t a;
	a.magic[0] = 83;
	a.magic[1] = 94;
	a.magic[2] = 121;
	TEST_FAIL_CHECK(doc_header_check_magic(&a));
}

void test_doc_header_from_file(void)
{
	dr4_doc_header_t a;
	FILE* test_fp;
	int head_result;
	unsigned char test_data[8] = {
		83, 94, 121,
		1, 0, 0,
		32, 0
	};
	test_fp = io_test_dump_fake(test_data, 8);
	head_result = doc_header_from_file(&a, test_fp);
	TEST_FAIL_CHECK(head_result == 1);
	TEST_FAIL_CHECK(doc_header_check_magic(&a));
	TEST_FAIL_CHECK(a.version[0] == 1);
	TEST_FAIL_CHECK(a.version[1] == 0);
	TEST_FAIL_CHECK(a.version[2] == 0);
	TEST_FAIL_CHECK(a.sizer == 32);
	fclose(test_fp);
}

int main(int argc, char const *argv[])
{
	test_doc_header_check_magic();
	test_doc_header_from_file();
	TEST_FAIL_RETURN
}
