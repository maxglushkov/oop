#include <iostream>
#include "CMyString.h"

CMyString::CMyString(const char * pString, size_t length)
	:CMyString(length)
{
	if (length)
	{
		memcpy(m_str, pString, length);
	}
}

int CMyString::Compare(CMyString const& lhs, CMyString const& rhs)
{
	const char * l = lhs.m_str;
	const char * r = rhs.m_str;
	const char *const lEnd = l + lhs.m_length;
	const char *const rEnd = r + rhs.m_length;

	for (; l != lEnd && r != rEnd; ++l, ++r)
	{
		if (const int cmp = *l - *r)
		{
			return cmp;
		}
	}
	return (l != lEnd) - (r != rEnd);
}

CMyString operator +(CMyString const& lhs, CMyString const& rhs)
{
	CMyString result(lhs.m_length + rhs.m_length);
	memcpy(result.m_str, lhs.m_str, lhs.m_length);
	memcpy(result.m_str + lhs.m_length, rhs.m_str, rhs.m_length);
	return result;
}

CMyString CMyString::SubString(size_t start, size_t length)const
{
	if (start > m_length)
	{
		throw std::out_of_range("start position exceeds string length");
	}
	return CMyString(m_str + start, std::min(length, m_length - start));
}

void CMyString::ThrowIndexIsOutOfRange()
{
	throw std::out_of_range("no character at requested index");
}

std::ostream & operator <<(std::ostream & output, CMyString const& string)
{
	return output.write(string.GetStringData(), string.GetLength());
}
