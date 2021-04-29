find_package(Catch2 REQUIRED)

add_executable(
	tests
	main.cpp
	CCircle.cpp
	CLineSegment.cpp
	CPoint.cpp
	CRectangle.cpp
	CTriangle.cpp
	$<TARGET_OBJECTS:shapes>
)

include(Catch)
catch_discover_tests(tests)
