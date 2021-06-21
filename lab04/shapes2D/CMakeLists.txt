cmake_minimum_required(VERSION 3.9.2)
project(Shapes2D VERSION 0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

enable_testing()
add_subdirectory(tests)

add_subdirectory(canvas)
add_subdirectory(shapes)

add_library(
	testable OBJECT
	shapes-array.cpp
)

add_executable(
	shapes2D
	main.cpp
	$<TARGET_OBJECTS:canvas>
	$<TARGET_OBJECTS:shapes>
	$<TARGET_OBJECTS:testable>
)

target_link_libraries(
	shapes2D
	${SDL2_GFX_LIBRARIES}
)
