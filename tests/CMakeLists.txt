# dr4-debug testing dir #

include_directories(${PROJECT_SOURCE_DIR}/lsrc)
# Test Definitions #
# 1. DR4_DEBUG_TDIR - the directory where test files are dumped.
####################
add_definitions(-DDR4_DEBUG_TDIR="${CMAKE_CURRENT_BINARY_DIR}/tests")

# Library to facilitate dumping and writing bytes easily to specific #
# files for testing purposes. #
add_library(io_test_help io_test_help.c)

add_executable(test_doc_info test_doc_info.c)
target_link_libraries(test_doc_info dr4-debug-lib io_test_help)
add_test(test_doc_info test_doc_info)
