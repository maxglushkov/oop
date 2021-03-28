#include <catch2/catch.hpp>
#include <sstream>
#include "../counter.h"
using std::istringstream;

TEST_CASE("Multiple input streams")
{
	WordCounts wordCounts;

	istringstream first("123\n456\t123");
	REQUIRE(CountWords(first, wordCounts));
	REQUIRE(wordCounts == WordCounts {
		{"123", 2},
		{"456", 1}
	});

	istringstream second("123\n456\t123");
	REQUIRE(CountWords(second, wordCounts));
	REQUIRE(wordCounts == WordCounts {
		{"123", 4},
		{"456", 2}
	});
}

TEST_CASE("Streams without words")
{
	WordCounts wordCounts;

	istringstream whitespace("  \r\t \n\t\r\n \n");
	REQUIRE(CountWords(whitespace, wordCounts));
	REQUIRE(wordCounts.empty());

	istringstream empty("");
	REQUIRE(CountWords(empty, wordCounts));
	REQUIRE(wordCounts.empty());

	REQUIRE(CountWords(empty, wordCounts));
	REQUIRE(wordCounts.empty());
}

TEST_CASE("Different character cases")
{
	WordCounts wordCounts;

	istringstream input("  WORDслово\rСл0в0  Слово\r\nСЛОВО\tword слово  \nWoRd\nW0rd\n");
	REQUIRE(CountWords(input, wordCounts));
	REQUIRE(wordCounts == WordCounts {
		{"WORDслово", 1},
		{"Сл0в0", 1},
		{"Слово", 1},
		{"СЛОВО", 1},
		{"word", 1},
		{"слово", 1},
		{"WoRd", 1},
		{"W0rd", 1}
	});
}
