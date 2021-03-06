#include <catch2/catch.hpp>
#include "../primes.h"

TEST_CASE("Negative upper bound")
{
	REQUIRE(GeneratePrimeNumbersSet(-1).size() == 0);
}

TEST_CASE("Upper bounds in range [0; 10]")
{
	REQUIRE(GeneratePrimeNumbersSet(0).size() == 0);
	REQUIRE(GeneratePrimeNumbersSet(1).size() == 0);
	REQUIRE(GeneratePrimeNumbersSet(2).size() == 1);
	REQUIRE(GeneratePrimeNumbersSet(3).size() == 2);
	REQUIRE(GeneratePrimeNumbersSet(4).size() == 2);
	REQUIRE(GeneratePrimeNumbersSet(5).size() == 3);
	REQUIRE(GeneratePrimeNumbersSet(6).size() == 3);
	REQUIRE(GeneratePrimeNumbersSet(7).size() == 4);
	REQUIRE(GeneratePrimeNumbersSet(8).size() == 4);
	REQUIRE(GeneratePrimeNumbersSet(9).size() == 4);
	REQUIRE(GeneratePrimeNumbersSet(10).size() == 4);
}

TEST_CASE("Large upper bound (100000000)")
{
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}
