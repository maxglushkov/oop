find_package(Catch2 REQUIRED)

add_executable(
	tests
	main.cpp
	CMyArray.cpp
)

include(Catch)
catch_discover_tests(tests)
