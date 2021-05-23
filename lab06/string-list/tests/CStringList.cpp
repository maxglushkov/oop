#include <catch2/catch.hpp>
#include "../CStringList.h"
using std::string;

TEST_CASE("Checking empty string list")
{
	CStringList list;
	REQUIRE(list.Size() == 0);
	REQUIRE(list.IsEmpty());
	REQUIRE(list.begin() == list.end());
	REQUIRE(list.begin() == list.cend());
	REQUIRE(list.cbegin() == list.end());
	REQUIRE(list.rbegin() == list.rend());
	REQUIRE(list.rbegin() == list.crend());
	REQUIRE(list.crbegin() == list.rend());
	for ([[maybe_unused]] string & str: list)
	{
		REQUIRE(false);
	}

	CStringList copied(list);
	REQUIRE(copied.IsEmpty());
	REQUIRE(copied.begin() == copied.end());
	REQUIRE(copied.begin() != list.begin());
	REQUIRE(list.begin() == list.end());

	CStringList moved(std::move(list));
	REQUIRE(moved.IsEmpty());
	REQUIRE(moved.begin() == moved.end());
	REQUIRE(moved.begin() != list.begin());
	REQUIRE(list.begin() == list.end());
}

TEST_CASE("Appending strings to the ends and clearing the list")
{
	CStringList list;
	const auto endIt = list.cend();
	const auto rbeginIt = list.crbegin();

	list.PushBack("First");
	list.PushBack("Second");
	list.PushFront("Zeroth");

	REQUIRE(list.Size() == 3);
	REQUIRE(list.cbegin() != endIt);
	REQUIRE(list.cend() == endIt);
	REQUIRE(list.crbegin() == rbeginIt);
	REQUIRE(list.crend() != rbeginIt);

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
	REQUIRE(list.crbegin() == rbeginIt);
	REQUIRE(list.crend() == rbeginIt);

	list.PushFront("First");
	list.PushBack("Second");
	list.PushFront("Zeroth");

	REQUIRE(list.Size() == 3);
	REQUIRE(list.cbegin() != endIt);
	REQUIRE(list.cend() == endIt);
	REQUIRE(list.crbegin() == rbeginIt);
	REQUIRE(list.crend() != rbeginIt);

	auto rit = list.crend();
	REQUIRE_THROWS(*rit);
	REQUIRE(*--rit == "Zeroth");
	REQUIRE(*--rit == "First");
	REQUIRE(*--rit == "Second");
	REQUIRE_THROWS(--rit);
	REQUIRE(rit == list.crbegin());
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
	REQUIRE_THROWS(list.Erase(it));
	REQUIRE(list.Size() == 2);

	it = list.Insert(it, "Third");
	REQUIRE(*it-- == "Third");
	REQUIRE(*it-- == "Second");
	REQUIRE(*it == "First");
	REQUIRE(list.Size() == 3);

	it = list.Erase(it);
	REQUIRE(*it == "Second");
	REQUIRE_THROWS(it--);
	REQUIRE(it == list.begin());
	REQUIRE(list.Size() == 2);

	it = list.Erase(it);
	REQUIRE(it == list.begin());
	REQUIRE(*it == "Third");
	REQUIRE(list.Size() == 1);

	it = list.Erase(it);
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

TEST_CASE("Checking whether string lists can be copied and moved")
{
	CStringList original;
	original.PushBack("First");
	original.PushBack("Second");
	original.PushBack("Third");
	REQUIRE(original.Size() == 3);

	std::array<const string *, 3> addresses;
	auto addrIt = addresses.begin();
	for (string const& str: original)
	{
		*addrIt++ = &str;
	}

	CStringList copied(original);
	REQUIRE(original.Size() == 3);
	REQUIRE(copied.Size() == 3);
	for (auto it1 = copied.begin(), it2 = original.begin(); it1 != copied.end(); ++it1, ++it2)
	{
		REQUIRE(it1 != it2);
		REQUIRE(*it1 == *it2);
		REQUIRE(&*it1 != &*it2);
	}
	for (auto it1 = copied.rbegin(), it2 = original.rbegin(); it1 != copied.rend(); ++it1, ++it2)
	{
		REQUIRE(it1 != it2);
		REQUIRE(*it1 == *it2);
		REQUIRE(&*it1 != &*it2);
	}

	CStringList moved(std::move(original));
	REQUIRE(original.IsEmpty());
	REQUIRE(original.begin() == original.end());
	REQUIRE(moved.Size() == 3);
	addrIt = addresses.begin();
	for (string const& str: moved)
	{
		REQUIRE(*addrIt++ == &str);
	}

	original.PushBack("");
	REQUIRE(original.Size() == 1);

	original = copied;
	REQUIRE(copied.Size() == 3);
	REQUIRE(original.Size() == 3);
	for (auto it1 = original.begin(), it2 = copied.begin(); it1 != original.end(); ++it1, ++it2)
	{
		REQUIRE(it1 != it2);
		REQUIRE(*it1 == *it2);
		REQUIRE(&*it1 != &*it2);
	}
	for (auto it1 = original.rbegin(), it2 = copied.rbegin(); it1 != original.rend(); ++it1, ++it2)
	{
		REQUIRE(it1 != it2);
		REQUIRE(*it1 == *it2);
		REQUIRE(&*it1 != &*it2);
	}

	original = std::move(moved);
	REQUIRE(moved.IsEmpty());
	REQUIRE(moved.begin() == moved.end());
	REQUIRE(original.Size() == 3);
	addrIt = addresses.begin();
	for (string const& str: moved)
	{
		REQUIRE(*addrIt++ == &str);
	}
}
