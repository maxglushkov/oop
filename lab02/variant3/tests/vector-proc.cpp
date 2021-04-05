#include <catch2/catch.hpp>
#include <sstream>
#include "../vector-proc.h"

TEST_CASE("Checking whether vectors can be read")
{
	DoubleVector vector;

	std::istringstream fail("\r  -1\t0\n 5a\n3\n");
	REQUIRE(!ReadVector(fail, vector));
	REQUIRE(vector == DoubleVector{-1, 0, 5});

	std::istringstream good("\n3\n");
	REQUIRE(ReadVector(good, vector));
	REQUIRE(vector == DoubleVector{-1, 0, 5, 3});
}

TEST_CASE("Checking whether vectors can be processed")
{
	DoubleVector vector{12, 3, 20.5, -8, 0, 1e-10, 21.5, -4.00001, 2, 1e-10 - 1};

	ProcessVector(vector);
	REQUIRE(vector == DoubleVector{18, 4.5, 20.5, -8, 0, 1e-10, 21.5, -4.00001, 2, 1e-10 - 1});
}

TEST_CASE("Checking how bad vectors are processed")
{
	DoubleVector vector{3};

	ProcessVector(vector);
	REQUIRE(vector == DoubleVector{3});
}

TEST_CASE("Checking whether vectors can be written")
{
	DoubleVector vector{18, 4.5, 0, 0.0000000001, -4.00001, -0.9999999999};

	std::ostringstream output;
	REQUIRE(WriteVector(output, vector));
	REQUIRE(output.str() == "18 4.5 0 1e-10 -4.00001 -1 \n");
}
