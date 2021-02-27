cmake_minimum_required(VERSION 3.9.2)
project(replace VERSION 0.0 LANGUAGES CXX)
enable_testing()

find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(DOXYGEN_EXTRACT_ALL YES)
	doxygen_add_docs(docs .)
endif()

set(
	SOURCES
	main.cpp
	replace.cpp
)
add_executable(replace ${SOURCES})
set_target_properties(
	replace PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

add_test(
	NAME all
	COMMAND "${CMAKE_SOURCE_DIR}/tests/test" "${CMAKE_BINARY_DIR}/replace"
)
