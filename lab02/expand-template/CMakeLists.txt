cmake_minimum_required(VERSION 3.9.2)
project(Expand-Template VERSION 0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

enable_testing()
add_subdirectory(tests)

add_library(
	testable OBJECT
	template.cpp
	trie.cpp
)

add_executable(
	expand-template
	main.cpp
	$<TARGET_OBJECTS:testable>
)
