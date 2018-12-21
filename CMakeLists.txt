cmake_minimum_required(VERSION 3.5)

# Project dr4-debug begins here #
PROJECT(dr4-debug)

# Version Tracker for dr4 #
# Only change if supported version of dr4 changes #
###################################################
SET(dr4_version_release 1)
SET(dr4_version_sub 0)
SET(dr4_version_patch 0)
SET(dr4_version "${dr4_version_release}.${dr4_version_sub}.${dr4_version_patch}")

string(TIMESTAMP dr4_build_time)

# Enables Testing for project #
enable_testing()

add_subdirectory(tests)

SET(dr4_debug_sources
    lsrc/doc_info.c
    lsrc/row_info.c
)

# dr4-debug defs #
# Available definitions #
# 1. DR4_ONLY_32B - If defined will support only the 32-bit variety of dr4
# 2. DR4_VERSION_RE - denotes the release version byte, to check for compatability.
# 3. DR4_VERSION_SUB - denotes the sub version byte
# 4. DR4_VERSION_PATCH - denotes the patch version byte
# note: if version defs not present, defaults to 1.0.0
##########################
add_definitions(-DDR4_ONLY_32B -DDR4_VERSION_RE=${dr4_version_release} -DDR4_VERSION_SUB=${dr4_version_sub} -DDR4_VERSION_PATCH=${dr4_version_patch})
##########################

# dr4-debug static lib #
add_library(dr4-debug-lib STATIC "${dr4_debug_sources}")

# The dr4-debug executable #
add_executable(dr4-debug main/main.c)
target_link_libraries(dr4-debug dr4-debug-lib)
target_include_directories(dr4-debug PUBLIC ${PROJECT_SOURCE_DIR}/lsrc)

## Copies the license file to the binary dir ##
file(COPY ${PROJECT_SOURCE_DIR}/LICENSE.md DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Writes build version to receipt file.
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/build_receipt.txt "dr4-debug Build\n Supports dr4 Version ${dr4-h_version}\n  Built at : ${dr4_build_time}\n...............\n")
