#include <catch2/catch.hpp>
#include "../primes.h"

TEST_CASE("Negative upper bound")
{
	REQUIRE(GeneratePrimeNumbersSet(-1).size() == 0);
}

TEST_CASE("Upper bounds in range [0; 10]")
{
	const std::set<int> PRIME_NUMBERS{2, 3, 5, 7};
	for (int upperBound = 0; upperBound <= 10; ++upperBound)
	{
		REQUIRE(std::equal(
			PRIME_NUMBERS.begin(), PRIME_NUMBERS.upper_bound(upperBound),
			GeneratePrimeNumbersSet(upperBound).begin()
		));
	}
}

TEST_CASE("Large upper bound (100000000)")
{
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}
