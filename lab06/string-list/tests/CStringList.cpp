#include <catch2/catch.hpp>
#include "../CStringList.h"
using std::string;

TEST_CASE("Checking empty string list")
{
	CStringList list;
	REQUIRE(list.Size() == 0);
	REQUIRE(list.IsEmpty());
	REQUIRE(list.begin() == list.end());
	REQUIRE(list.cbegin() == list.cend());
	REQUIRE(list.rbegin() == list.rend());
	REQUIRE(list.crbegin() == list.crend());
	for ([[maybe_unused]] string & str: list)
	{
		REQUIRE(false);
	}
}

TEST_CASE("Appending strings to the ends and clearing the list")
{
	CStringList list;
	const auto endIt = list.cend();
	const auto rendIt = list.crend();

	list.PushBack("First");
	list.PushBack("Second");
	list.PushFront("Zeroth");

	REQUIRE(list.Size() == 3);
	REQUIRE(list.cbegin() != endIt);
	REQUIRE(list.cend() == endIt);
	REQUIRE(list.crbegin() != rendIt);
	REQUIRE(list.crend() == rendIt);

	auto it = endIt;
	REQUIRE_THROWS(*it);
	REQUIRE(*--it == "Second");
	REQUIRE(*--it == "First");
	REQUIRE(*--it == "Zeroth");
	REQUIRE_THROWS(--it);
	REQUIRE(it == list.cbegin());

	list.Clear();
	REQUIRE(list.IsEmpty());
	REQUIRE(list.cbegin() == endIt);
	REQUIRE(list.cend() == endIt);
	REQUIRE(list.crbegin() == rendIt);
	REQUIRE(list.crend() == rendIt);

	list.PushFront("First");
	list.PushBack("Second");
	list.PushFront("Zeroth");

	REQUIRE(list.Size() == 3);
	REQUIRE(list.cbegin() != endIt);
	REQUIRE(list.cend() == endIt);
	REQUIRE(list.crbegin() != rendIt);
	REQUIRE(list.crend() == rendIt);

	it = rendIt;
	REQUIRE_THROWS(*it--);
	REQUIRE(*it-- == "Zeroth");
	REQUIRE(*it-- == "First");
	REQUIRE_THROWS(it--);
	REQUIRE(*it == "Second");
	REQUIRE(it == list.crbegin());
}

TEST_CASE("Inserting and erasing strings")
{
	CStringList list;

	auto it = list.Insert(list.begin(), "Second");
	it = list.Insert(it, "First");
	REQUIRE(it == list.begin());
	REQUIRE(*it++ == "First");
	REQUIRE(*it++ == "Second");
	REQUIRE(list.Size() == 2);

	REQUIRE(it == list.end());
	REQUIRE_THROWS(*it);
	REQUIRE_THROWS(it++);
	REQUIRE(it == list.end());
	REQUIRE_THROWS(list.Erase(std::move(it)));
	REQUIRE(list.Size() == 2);

	it = list.Insert(list.rbegin(), "Third");
	REQUIRE(*it == "Third");
	REQUIRE(*++it == "Second");
	REQUIRE(list.Size() == 3);

	it = list.Erase(std::move(it));
	REQUIRE(*it == "First");
	REQUIRE(++it == list.rend());
	REQUIRE_THROWS(*it);
	REQUIRE_THROWS(++it);
	REQUIRE(it == list.rend());
	REQUIRE(list.Size() == 2);

	it = list.Erase(list.begin());
	REQUIRE(it == list.begin());
	REQUIRE(*it == "Third");
	REQUIRE(list.Size() == 1);

	it = list.Erase(std::move(it));
	REQUIRE(it == list.begin());
	REQUIRE(it == list.end());
	REQUIRE(list.IsEmpty());
}

TEST_CASE("Checking whether STL algorithms work on string list")
{
	const std::array<string, 6> originalList{"", "1st", "", "2nd", "3rd", ""};
	CStringList list;
	for (string const& str: originalList)
	{
		list.PushBack(str);
	}

	REQUIRE(std::find(list.cbegin(), list.cend(), "")->empty());

	REQUIRE(std::count_if(
		list.crbegin(), list.crend(),
		[](string const& str){
			return str.empty();
		}
	) == 3);

	std::reverse(list.begin(), list.end());
	auto it = originalList.rbegin();
	for (string const& str: list)
	{
		REQUIRE(str == *it++);
	}

	std::fill(list.rbegin(), list.rend(), "");
	for (string & str: list)
	{
		REQUIRE(str.empty());
		str = *--it;
	}

	REQUIRE(std::equal(list.cbegin(), list.cend(), originalList.cbegin()));
}
