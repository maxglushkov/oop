cmake_minimum_required(VERSION 3.9.2)
project(StringList VERSION 0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_CXX_EXTENSIONS NO)

enable_testing()
add_subdirectory(tests)

add_library(
	testable OBJECT
	CStringList.cpp
)
