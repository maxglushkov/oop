#include <numeric>
#include "CRational.h"
using std::gcd, std::lcm;

CRational & CRational::operator +=(CRational const& other)
{
	const int denominator = lcm(GetDenominator(), other.GetDenominator());
	m_rational = FromCheckedDenominator(
		GetNumerator() * (denominator / GetDenominator()) + other.GetNumerator() * (denominator / other.GetDenominator()),
		denominator
	);
	return *this;
}

CRational & CRational::operator -=(CRational const& other)
{
	const int denominator = lcm(GetDenominator(), other.GetDenominator());
	m_rational = FromCheckedDenominator(
		GetNumerator() * (denominator / GetDenominator()) - other.GetNumerator() * (denominator / other.GetDenominator()),
		denominator
	);
	return *this;
}

CRational & CRational::operator *=(CRational const& other)
{
	const Rational rational = FromCheckedDenominator(other.GetNumerator(), GetDenominator());
	m_rational = FromCheckedDenominator(GetNumerator(), other.GetDenominator());
	m_rational.numerator *= rational.numerator;
	m_rational.denominator *= rational.denominator;
	return *this;
}

CRational & CRational::operator /=(CRational const& other)
{
	const Rational rational = FromUnchecked(GetNumerator(), other.GetNumerator());
	m_rational = FromCheckedDenominator(other.GetDenominator(), GetDenominator());
	m_rational.numerator *= rational.numerator;
	m_rational.denominator *= rational.denominator;
	return *this;
}

std::istream & operator >>(std::istream & input, CRational & rational)
{
	int numerator;
	input >> numerator;
	if (input.peek() != '/')
	{
		if (input)
		{
			rational = numerator;
		}
	}
	else
	{
		int denominator;
		input.ignore() >> denominator;
		if (input)
		{
			try
			{
				rational = CRational::FromUnchecked(numerator, denominator);
			}
			catch (std::invalid_argument e)
			{
				input.setstate(std::ios::failbit);
			}
		}
	}
	if (!input)
	{
		rational = 0;
	}
	return input;
}

CRational::Rational CRational::FromCheckedDenominator(int numerator, int denominator)
{
	const int factor = gcd(numerator, denominator);
	return {numerator / factor, denominator / factor};
}

CRational::Rational CRational::FromUnchecked(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("zero is not a valid divisor");
	}

	int factor = gcd(numerator, denominator);
	if (denominator < 0)
	{
		factor = -factor;
	}
	return {numerator / factor, denominator / factor};
}

std::ostream & operator <<(std::ostream & output, CRational const& rational)
{
	output << rational.GetNumerator();
	if (rational.GetDenominator() != 1)
	{
		output << '/' << rational.GetDenominator();
	}
	return output;
}
