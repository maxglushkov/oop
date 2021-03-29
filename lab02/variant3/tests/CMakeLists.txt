find_package(Catch2 REQUIRED)

add_executable(
	tests
	main.cpp
	vector-proc.cpp
	$<TARGET_OBJECTS:testable>
)

include(Catch)
catch_discover_tests(tests)
