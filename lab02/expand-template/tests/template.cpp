#include <catch2/catch.hpp>
#include "../template.h"

TEST_CASE("Checking whether templates can be expanded")
{
	REQUIRE(
		ExpandTemplate(
			"Hello, %USER_NAME%. Today is {WEEK_DAY}.",
			{
				{"%USER_NAME%", "Ivan Petrov"},
				{"{WEEK_DAY}", "Friday"}
			}
		) == "Hello, Ivan Petrov. Today is Friday."
	);
}

TEST_CASE("Checking whether recursion is possible")
{
	REQUIRE(
		ExpandTemplate(
			"Hello, %USER_NAME%. Today is {WEEK_DAY}.",
			{
				{"%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}"},
				{"{WEEK_DAY}", "Friday. {WEEK_DAY}"}
			}
		) == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}."
	);
}

TEST_CASE("Checking whether the longest match takes precedence")
{
	REQUIRE(
		ExpandTemplate(
			"-AABBCCCCCABC+",
			{
				{"A", "[a]"},
				{"AA", "[aa]"},
				{"B", "[b]"},
				{"BB", "[bb]"},
				{"C", "[c]"},
				{"CC", "[cc]"}
			}
		) == "-[aa][bb][cc][cc][c][a][b][c]+"
	);
}
