#include "test_failures.h"
#include "doc_info.h"




void test_doc_header_check_magic(void)
{
	dr4_doc_header_t a;
	a.magic[0] = 83;
	a.magic[1] = 94;
	a.magic[2] = 121;
	TEST_FAIL_CHECK(doc_header_check_magic(&a));
}

int main(int argc, char const *argv[])
{
	test_doc_header_check_magic();
	TEST_FAIL_RETURN
}
