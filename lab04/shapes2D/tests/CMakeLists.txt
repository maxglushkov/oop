find_package(Catch2 REQUIRED)

add_executable(
	tests
	main.cpp
	CCircle.cpp
	CLineSegment.cpp
	CPoint.cpp
	CRectangle.cpp
	CTriangle.cpp
	shapes-array.cpp
	$<TARGET_OBJECTS:shapes>
	$<TARGET_OBJECTS:testable>
)

include(Catch)
catch_discover_tests(tests)
