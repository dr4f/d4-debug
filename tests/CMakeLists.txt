# dr4-debug testing dir #

include_directories(${PROJECT_SOURCE_DIR}/lsrc)

add_executable(test_doc_info test_doc_info.c)
target_link_libraries(test_doc_info dr4-debug-lib)
add_test(test_doc_info test_doc_info)
