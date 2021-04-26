#include <catch2/catch.hpp>
#include <sstream>
#include "../CRational.h"

TEST_CASE("Checking default rational value")
{
	CRational rational;
	REQUIRE(rational.GetNumerator() == 0);
	REQUIRE(rational.GetDenominator() == 1);
	REQUIRE(rational.ToDouble() == 0.0);
}

TEST_CASE("Checking rational value constructed from integer")
{
	CRational rational = 0x7337;
	REQUIRE(rational.GetNumerator() == 0x7337);
	REQUIRE(rational.GetDenominator() == 1);
	REQUIRE(rational.ToDouble() == 29495.0);
}

TEST_CASE("Checking rational values constructed from numerator and denominator")
{
	REQUIRE_THROWS(CRational(1, 0));

	CRational rational(9, -6);
	REQUIRE(rational.GetNumerator() == -3);
	REQUIRE(rational.GetDenominator() == 2);
	REQUIRE(rational.ToDouble() == -1.5);

	rational = CRational(99, 4);
	REQUIRE(rational.GetNumerator() == 99);
	REQUIRE(rational.GetDenominator() == 4);
	REQUIRE(rational.ToDouble() == 24.75);
}

TEST_CASE("Checking convertion to compound fraction")
{
	auto pair = CRational().ToCompoundFraction();
	REQUIRE(pair.first == 0);
	REQUIRE(pair.second == 0);

	pair = CRational(250).ToCompoundFraction();
	REQUIRE(pair.first == 250);
	REQUIRE(pair.second == 0);

	pair = CRational(-4, 8).ToCompoundFraction();
	REQUIRE(pair.first == 0);
	REQUIRE(pair.second == CRational(-1, 2));

	pair = CRational(30, 7).ToCompoundFraction();
	REQUIRE(pair.first == 4);
	REQUIRE(pair.second == CRational(2, 7));

	pair = CRational(-30, 7).ToCompoundFraction();
	REQUIRE(pair.first == -4);
	REQUIRE(pair.second == CRational(-2, 7));
}

TEST_CASE("Checking unary operations")
{
	CRational rational(3, 5);
	REQUIRE(+rational == rational);
	REQUIRE(-rational == CRational(-3, 5));

	rational = 0;
	REQUIRE(-rational == rational);
}

TEST_CASE("Checking addition and subtraction")
{
	REQUIRE(CRational(1, 2) + CRational(1, 6) == CRational(2, 3));
	REQUIRE(CRational(1, 2) + 1 == CRational(3, 2));
	REQUIRE(1 + CRational(1, 2) == CRational(3, 2));

	REQUIRE(CRational(1, 2) - CRational(1, 6) == CRational(1, 3));
	REQUIRE(CRational(1, 2) - 1 == CRational(-1, 2));
	REQUIRE(1 - CRational(1, 2) == CRational(1, 2));

	CRational rational(1, 2);
	rational += CRational(1, 6);
	REQUIRE(rational == CRational(2, 3));

	rational = CRational(1, 2);
	rational += 1;
	REQUIRE(rational == CRational(3, 2));

	rational = CRational(1, 2);
	rational -= CRational(1, 6);
	REQUIRE(rational == CRational(1, 3));

	rational = CRational(1, 2);
	rational -= 1;
	REQUIRE(rational == CRational(-1, 2));
}

TEST_CASE("Checking multiplication and dividing")
{
	REQUIRE(CRational(1, 2) * CRational(2, 3) == CRational(1, 3));
	REQUIRE(CRational(1, 2) * -3 == CRational(-3, 2));
	REQUIRE(7 * CRational(2, 3) == CRational(14, 3));

	REQUIRE(CRational(1, 2) / CRational(2, 3) == CRational(3, 4));
	REQUIRE(CRational(1, 2) / 5 == CRational(1, 10));
	REQUIRE(7 / CRational(2, 3) == CRational(21, 2));
	REQUIRE_THROWS(CRational(1) / 0);

	CRational rational(1, 2);
	rational *= CRational(2, 3);
	REQUIRE(rational == CRational(1, 3));

	rational = CRational(1, 2);
	rational *= 3;
	REQUIRE(rational == CRational(3, 2));

	rational = CRational(1, 2);
	rational /= CRational(2, 3);
	REQUIRE(rational == CRational(3, 4));

	rational = CRational(1, 2);
	rational /= 3;
	REQUIRE(rational == CRational(1, 6));

	rational = CRational(3, 4);
	rational /= CRational(3, 8);
	REQUIRE(rational == 2);
}

TEST_CASE("Checking rational equivalence")
{
	REQUIRE(CRational(1, 2) == CRational(1, 2));
	REQUIRE_FALSE(CRational(1, 2) == CRational(2, 3));
	REQUIRE(CRational(4, 1) == 4);
	REQUIRE_FALSE(CRational(1, 2) == 7);
	REQUIRE(3 == CRational(3, 1));
	REQUIRE_FALSE(3 == CRational(2, 3));

	REQUIRE_FALSE(CRational(1, 2) != CRational(1, 2));
	REQUIRE(CRational(1, 2) != CRational(2, 3));
	REQUIRE_FALSE(CRational(4, 1) != 4);
	REQUIRE(CRational(1, 2) != 7);
	REQUIRE_FALSE(3 != CRational(3, 1));
	REQUIRE(3 != CRational(2, 3));
}

TEST_CASE("Checking rational ordering")
{
	REQUIRE(CRational(1, 2) > CRational(1, 3));
	REQUIRE_FALSE(CRational(1, 2) > CRational(1, 2));
	REQUIRE_FALSE(CRational(1, 3) > CRational(1, 2));

	REQUIRE_FALSE(CRational(1, 2) <= CRational(1, 3));
	REQUIRE(CRational(1, 3) <= CRational(1, 3));
	REQUIRE(CRational(1, 3) <= CRational(1, 2));

	REQUIRE(CRational(3, 1) > 2);
	REQUIRE_FALSE(CRational(3, 1) > 3);
	REQUIRE_FALSE(2 > CRational(3, 1));

	REQUIRE(CRational(1, 2) < 7);
	REQUIRE_FALSE(CRational(7) < 7);
	REQUIRE_FALSE(7 < CRational(1, 2));

	REQUIRE(3 <= CRational(7, 2));
	REQUIRE(CRational(7, 2) <= CRational(7, 2));
	REQUIRE_FALSE(CRational(7, 2) <= 3);

	REQUIRE_FALSE(3 >= CRational(8, 2));
	REQUIRE(CRational(12, 3) >= CRational(8, 2));
	REQUIRE(CRational(8, 2) >= 3);
}

TEST_CASE("Checking formatted input-output")
{
	CRational rational;
	std::istringstream input(" 4/ -6 1/0\n -1 / 2 3//0");
	std::ostringstream output;

	REQUIRE(input >> rational);
	REQUIRE(input.tellg() == 6);
	output << rational << '\n';

	REQUIRE_FALSE(input >> rational);
	input.clear();
	REQUIRE(input.tellg() == 10);
	output << rational << '\n';

	REQUIRE(input >> rational);
	REQUIRE(input.tellg() == 14);
	output << rational << '\n';

	REQUIRE_FALSE(input >> rational);
	input.clear();
	REQUIRE(input.tellg() == 15);
	output << rational << '\n';

	REQUIRE(input.ignore() >> rational);
	REQUIRE(input.tellg() == 18);
	output << rational << '\n';

	REQUIRE_FALSE(input >> rational);
	input.clear();
	REQUIRE(input.tellg() == 21);
	output << rational << '\n';

	REQUIRE_FALSE(input >> rational);
	input.clear();
	REQUIRE(input.tellg() == 21);
	output << rational << '\n';

	REQUIRE(output.str() == "-2/3\n0\n-1\n0\n2\n0\n0\n");
}
