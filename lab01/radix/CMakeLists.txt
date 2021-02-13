cmake_minimum_required(VERSION 3.9.2)
project(radix VERSION 0.0 LANGUAGES CXX)

find_package(Doxygen REQUIRED)
set(DOXYGEN_EXTRACT_ALL YES)
doxygen_add_docs(docs .)

set(
	SOURCES
	main.cpp
	format-int.cpp
)
add_executable(radix ${SOURCES})
set_target_properties(
	radix PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED NO
	CXX_EXTENSIONS NO
)
