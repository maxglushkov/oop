#include <catch2/catch.hpp>
#include "../FindMaxEx.h"

struct Sportsman
{
	std::string name;
	double height;
	double weight;
};

static bool LessByHeight(Sportsman const& lhs, Sportsman const& rhs)
{
	return lhs.height < rhs.height;
}

static bool LessByWeight(Sportsman const& lhs, Sportsman const& rhs)
{
	return lhs.weight < rhs.weight;
}

static bool LessThrow(Sportsman const& lhs, Sportsman const& rhs)
{
	throw std::pair(lhs, rhs);
}

TEST_CASE("Finding max element in empty vector")
{
	std::vector<Sportsman> sportsmen;

	Sportsman found;
	REQUIRE(!FindMax(sportsmen, found, LessByHeight));
	REQUIRE(found.name.empty());

	REQUIRE(!FindMax(sportsmen, found, LessByWeight));
	REQUIRE(found.name.empty());

	REQUIRE(!FindMax(sportsmen, found, LessThrow));
	REQUIRE(found.name.empty());
}

TEST_CASE("Finding max element in vector with single item")
{
	std::vector<Sportsman> sportsmen{
		{"Super Sports Man", 169.0, 59.8}
	};

	Sportsman found;
	REQUIRE(FindMax(sportsmen, found, LessByHeight));
	REQUIRE(found.name == "Super Sports Man");

	found = {};
	REQUIRE(FindMax(sportsmen, found, LessByWeight));
	REQUIRE(found.name == "Super Sports Man");

	found = {};
	REQUIRE(FindMax(sportsmen, found, LessThrow));
	REQUIRE(found.name == "Super Sports Man");
}

TEST_CASE("Finding max element in vector with multiple items")
{
	std::vector<Sportsman> sportsmen{
		{"High Sports Man", 178.9, 64.9},
		{"Super Sports Man", 169.0, 59.8},
		{"Heavy Sports Man", 171.1, 70.3}
	};

	Sportsman found;
	REQUIRE(FindMax(sportsmen, found, LessByHeight));
	REQUIRE(found.name == "High Sports Man");

	REQUIRE(FindMax(sportsmen, found, LessByWeight));
	REQUIRE(found.name == "Heavy Sports Man");

	REQUIRE_THROWS(FindMax(sportsmen, found, LessThrow));
	REQUIRE(found.name == "Heavy Sports Man");
}
