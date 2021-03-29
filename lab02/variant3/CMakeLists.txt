cmake_minimum_required(VERSION 3.9.2)
project(variant3 VERSION 0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_CXX_EXTENSIONS NO)

enable_testing()
add_subdirectory(tests)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(DOXYGEN_EXTRACT_ALL YES)
	doxygen_add_docs(docs .)
endif()

add_library(
	testable OBJECT
	vector-proc.cpp
)

add_executable(
	variant3
	main.cpp
	$<TARGET_OBJECTS:testable>
)
