#pragma once
#include <cstring>
#include <string>

class CMyString
{
public:
	CMyString()
		:CMyString(size_t(0))
	{
	}

	CMyString(CMyString && other)
	{
		memcpy(this, &other, sizeof(CMyString));
		new (&other) CMyString();
	}

	CMyString(CMyString const& other)
		:CMyString(other.m_str, other.m_length)
	{
	}

	CMyString(const char * pString)
		:CMyString(pString, strlen(pString))
	{
	}

	CMyString(const char * pString, size_t length);

	CMyString(std::string const& stlString)
		:CMyString(stlString.data(), stlString.length())
	{
	}

	~CMyString()
	{
		if (m_length)
		{
			delete[] m_str;
		}
	}

	static int Compare(CMyString const& lhs, CMyString const& rhs);

	CMyString & operator =(CMyString && other)
	{
		if (this != &other)
		{
			this->~CMyString();
			new (this) CMyString(std::move(other));
		}
		return *this;
	}

	CMyString & operator =(CMyString const& other)
	{
		if (this != &other)
		{
			*this = CMyString(other);
		}
		return *this;
	}

	friend CMyString operator +(CMyString const& lhs, CMyString const& rhs);

	CMyString & operator +=(CMyString const& other)
	{
		if (other.m_length)
		{
			*this = *this + other;
		}
		return *this;
	}

	char & operator [](size_t index)
	{
		if (index >= m_length)
		{
			ThrowIndexIsOutOfRange();
		}
		return m_str[index];
	}

	char operator [](size_t index)const
	{
		if (index >= m_length)
		{
			ThrowIndexIsOutOfRange();
		}
		return m_str[index];
	}

	size_t GetLength()const
	{
		return m_length;
	}

	const char * GetStringData()const
	{
		return m_str;
	}

	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

	void Clear()
	{
		if (m_length)
		{
			delete[] m_str;
			new (this) CMyString();
		}
	}

private:
	char * m_str;
	size_t m_length;

	explicit CMyString(size_t length)
		:m_length(length)
	{
		if (!length)
		{
			static char EMPTY[] = "";
			m_str = EMPTY;
		}
		else
		{
			m_str = new char[length + 1];
			m_str[length] = 0;
		}
	}

	[[noreturn]] static void ThrowIndexIsOutOfRange();
};

inline bool operator ==(CMyString const& lhs, CMyString const& rhs)
{
	return CMyString::Compare(lhs, rhs) == 0;
}

inline bool operator !=(CMyString const& lhs, CMyString const& rhs)
{
	return CMyString::Compare(lhs, rhs) != 0;
}

inline bool operator <(CMyString const& lhs, CMyString const& rhs)
{
	return CMyString::Compare(lhs, rhs) < 0;
}

inline bool operator >(CMyString const& lhs, CMyString const& rhs)
{
	return CMyString::Compare(lhs, rhs) > 0;
}

inline bool operator <=(CMyString const& lhs, CMyString const& rhs)
{
	return CMyString::Compare(lhs, rhs) <= 0;
}

inline bool operator >=(CMyString const& lhs, CMyString const& rhs)
{
	return CMyString::Compare(lhs, rhs) >= 0;
}

std::ostream & operator <<(std::ostream & output, CMyString const& string);
