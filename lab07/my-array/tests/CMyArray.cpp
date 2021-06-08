#include <catch2/catch.hpp>
#include <limits>
#include "../CMyArray.h"

template<typename T>
void TestMyArray(std::array<T, 3> const& testData)
{
	CMyArray<T> array;
	REQUIRE(array.Size() == 0);
	REQUIRE(array.Capacity() == 0);
	REQUIRE_THROWS(array[size_t(-1)]);
	REQUIRE_THROWS(array[0]);

	auto it = array.cbegin();
	REQUIRE_THROWS(--it);
	REQUIRE_THROWS(it--);
	REQUIRE(array.end() == it);
	REQUIRE_THROWS(*it);

	array.PushBack(testData[0]);
	REQUIRE(array.Size() == 1);
	REQUIRE(array.Capacity() == 1);
	REQUIRE(*it++ == testData[0]);

	array.PushBack(testData[1]);
	REQUIRE(array.Size() == 2);
	REQUIRE(array.Capacity() == 2);
	REQUIRE(*it++ == testData[1]);

	array.Resize(3);
	REQUIRE(array.Size() == 3);
	REQUIRE(array.Capacity() == 3);
	REQUIRE_THROWS(array[size_t(-1)]);
	REQUIRE(array[0] == testData[0]);
	REQUIRE(array[1] == testData[1]);
	REQUIRE_NOTHROW(array[2]);
	REQUIRE_THROWS(array[3]);

	REQUIRE_NOTHROW(*it++);
	REQUIRE_THROWS(*it);
	REQUIRE(it == array.cend());
	REQUIRE_THROWS(it++);
	REQUIRE_THROWS(++it);

	array[2] = array[1];
	REQUIRE(array[1] == testData[1]);
	REQUIRE(array[2] == testData[1]);
	REQUIRE(*--it == testData[1]);
	REQUIRE(it - 2 == array.begin());

	auto rit = array.crbegin();
	REQUIRE(*rit++ == testData[1]);
	REQUIRE(*rit++ == testData[1]);
	REQUIRE(*rit++ == testData[0]);
	REQUIRE_THROWS(*rit);
	REQUIRE(rit == array.rend());
	REQUIRE_THROWS(rit++);
	REQUIRE_THROWS(++rit);

	array.Resize(3);
	REQUIRE(array.Size() == 3);
	REQUIRE(array.Capacity() == 3);
	REQUIRE(*--rit == testData[0]);
	REQUIRE(*--rit == testData[1]);
	REQUIRE(*--rit == testData[1]);
	REQUIRE_THROWS(rit[-1]);

	array.Resize(1);
	REQUIRE(array.Size() == 1);
	REQUIRE(array.Capacity() == 3);
	const T *const address = &array[0];
	REQUIRE(array[0] == testData[0]);
	REQUIRE_THROWS(array[1]);
	REQUIRE_THROWS(rit + 1);
	REQUIRE_THROWS(rit -= 2);
	REQUIRE_THROWS(it -= 0);
	REQUIRE_THROWS(1 + it);
	REQUIRE(3 + rit == array.crend());

	CMyArray<T> copied(array);
	REQUIRE(array.Size() == 1);
	REQUIRE(array.Capacity() == 3);
	REQUIRE(copied.Size() == 1);
	REQUIRE(copied.Capacity() == 3);
	REQUIRE(copied[0] == array[0]);
	REQUIRE(&copied[0] != address);

	REQUIRE_NOTHROW(rit += 2);
	REQUIRE(array.rbegin() == rit - 0);
	REQUIRE(copied.rbegin() != rit);

	REQUIRE_NOTHROW(it += -2);
	REQUIRE_THROWS(it + 2);
	REQUIRE(1 + it == array.cend());
	REQUIRE(1 + it != copied.cend());

	CMyArray<T> moved(std::move(array));
	REQUIRE(array.Size() == 0);
	REQUIRE(array.Capacity() == 0);
	REQUIRE(moved.Size() == 1);
	REQUIRE(moved.Capacity() == 3);
	REQUIRE(&moved[0] == address);
	REQUIRE(it == array.cbegin());
	REQUIRE(it != moved.cbegin());

	array.PushBack(testData[2]);
	REQUIRE(array.Size() == 1);
	REQUIRE(array.Capacity() == 1);
	REQUIRE(it[0] == testData[2]);
	REQUIRE(it - array.end() == -1);
	REQUIRE(it - array.begin() == 0);
	REQUIRE(array.end() - it == 1);

	array = copied;
	REQUIRE(copied.Size() == 1);
	REQUIRE(copied.Capacity() == 3);
	REQUIRE(array.Size() == 1);
	REQUIRE(array.Capacity() == 3);
	REQUIRE(array[0] == copied[0]);
	REQUIRE(&array[0] != &copied[0]);
	REQUIRE_THROWS(rit < copied.crbegin());
	REQUIRE_THROWS(rit > copied.crbegin());
	REQUIRE(rit < array.crend());
	REQUIRE(rit <= array.crbegin());

	array = std::move(moved);
	REQUIRE(moved.Size() == 0);
	REQUIRE(moved.Capacity() == 0);
	REQUIRE(array.Size() == 1);
	REQUIRE(array.Capacity() == 3);
	REQUIRE(&array[0] == address);
	REQUIRE_THROWS(it <= moved.cbegin());
	REQUIRE_THROWS(it >= moved.cbegin());
	REQUIRE(it < array.cend());
	REQUIRE(it <= array.cbegin());

	array.Clear();
	REQUIRE(array.Size() == 0);
	REQUIRE(array.Capacity() == 3);
}

TEST_CASE("Checking CMyArray<std::string>")
{
	TestMyArray<std::string>({"First", "Second", ""});
}

TEST_CASE("Checking CMyArray<double>")
{
	TestMyArray<double>({-10, 0.001, -std::numeric_limits<double>::infinity()});
}

TEST_CASE("Checking static cast assignment")
{
	CMyArray<const char *> cstrArray;
	cstrArray.PushBack("First");
	cstrArray.PushBack("2nd");
	cstrArray.PushBack("");
	cstrArray.PushBack("Last");

	CMyArray<std::string> strArray;
	REQUIRE_NOTHROW(strArray = cstrArray);
	REQUIRE(std::equal(cstrArray.crbegin(), cstrArray.crend(), cstrArray.crbegin(), cstrArray.crend()));
}
