#pragma once
#include <iostream>

static_assert(sizeof(long long) == 2 * sizeof(int));

class CRational
{
public:
	CRational()
		:CRational(0)
	{
	}

	CRational(int value)
		:m_rational(FromNormalized(value, 1))
	{
	}

	CRational(int numerator, int denominator)
		:m_rational(FromUnchecked(numerator, denominator))
	{
	}

	int GetNumerator()const
	{
		return m_rational.numerator;
	}

	int GetDenominator()const
	{
		return m_rational.denominator;
	}

	double ToDouble()const
	{
		return double(GetNumerator()) / GetDenominator();
	}

	std::pair<int, CRational> ToCompoundFraction()const
	{
		return std::pair(
			GetNumerator() / GetDenominator(),
			CRational(FromNormalized(GetNumerator() % GetDenominator(), GetDenominator()))
		);
	}

	CRational operator +()const
	{
		return *this;
	}

	CRational operator -()const
	{
		return FromNormalized(-GetNumerator(), GetDenominator());
	}

	CRational & operator +=(CRational const& other);

	CRational & operator -=(CRational const& other);

	CRational & operator *=(CRational const& other);

	CRational & operator /=(CRational const& other);

	friend std::istream & operator >>(std::istream & input, CRational & rational);

private:
	struct Rational
	{
		int numerator, denominator;
	};

	Rational m_rational;

	CRational(Rational const& rational)
		:m_rational(rational)
	{
	}

	static Rational FromNormalized(int numerator, int denominator)
	{
		return {numerator, denominator};
	}

	static Rational FromCheckedDenominator(int numerator, int denominator);

	static Rational FromUnchecked(int numerator, int denominator);
};

inline CRational operator +(CRational lhs, CRational const& rhs)
{
	return lhs += rhs;
}

inline CRational operator -(CRational lhs, CRational const& rhs)
{
	return lhs -= rhs;
}

inline CRational operator *(CRational lhs, CRational const& rhs)
{
	return lhs *= rhs;
}

inline CRational operator /(CRational lhs, CRational const& rhs)
{
	return lhs /= rhs;
}

inline bool operator ==(CRational const& lhs, CRational const& rhs)
{
	return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
}

inline bool operator !=(CRational const& lhs, CRational const& rhs)
{
	return !(lhs == rhs);
}

inline bool operator <(CRational const& lhs, CRational const& rhs)
{
	return (long long)lhs.GetNumerator() * rhs.GetDenominator() < (long long)rhs.GetNumerator() * lhs.GetDenominator();
}

inline bool operator >(CRational const& lhs, CRational const& rhs)
{
	return (long long)lhs.GetNumerator() * rhs.GetDenominator() > (long long)rhs.GetNumerator() * lhs.GetDenominator();
}

inline bool operator <=(CRational const& lhs, CRational const& rhs)
{
	return !(lhs > rhs);
}

inline bool operator >=(CRational const& lhs, CRational const& rhs)
{
	return !(lhs < rhs);
}

std::ostream & operator <<(std::ostream & output, CRational const& rational);
