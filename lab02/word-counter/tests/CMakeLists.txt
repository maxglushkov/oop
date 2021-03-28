find_package(Catch2 REQUIRED)

add_executable(
	tests
	main.cpp
	counter.cpp
	$<TARGET_OBJECTS:testable>
)

include(Catch)
catch_discover_tests(tests)
