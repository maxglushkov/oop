#pragma once
#include <cstring>
#include <string>

class CMyString
{
	template<typename String, typename Char>
	class CIterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = Char;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type *;
		using reference = value_type &;

		CIterator & operator +=(difference_type offset)
		{
			m_index += offset;
			assert(m_index <= m_str->m_length);
			return *this;
		}

		friend CIterator operator +(CIterator iter, difference_type offset)
		{
			return iter += offset;
		}

		friend CIterator operator +(difference_type offset, CIterator iter)
		{
			return iter += offset;
		}

		CIterator & operator -=(difference_type offset)
		{
			return *this += -offset;
		}

		friend CIterator operator -(CIterator iter, difference_type offset)
		{
			return iter -= offset;
		}

		friend difference_type operator -(CIterator const& lhs, CIterator const& rhs)
		{
			assert(lhs.m_str == rhs.m_str);
			return lhs.m_index - rhs.m_index;
		}

		CIterator & operator ++()
		{
			return *this += 1;
		}

		CIterator operator ++(int)
		{
			CIterator saved = *this;
			++*this;
			return saved;
		}

		CIterator & operator --()
		{
			return *this -= 1;
		}

		CIterator operator --(int)
		{
			CIterator saved = *this;
			--*this;
			return saved;
		}

		reference operator [](difference_type offset)const
		{
			assert(m_index + offset < m_str->m_length);
			return m_str->m_str[m_index + offset];
		}

		reference operator *()const
		{
			return (*this)[0];
		}

		friend bool operator ==(CIterator const& lhs, CIterator const& rhs)
		{
			return lhs.m_str == rhs.m_str && lhs.m_index == rhs.m_index;
		}

		friend bool operator !=(CIterator const& lhs, CIterator const& rhs)
		{
			return !(lhs == rhs);
		}

		friend bool operator <(CIterator const& lhs, CIterator const& rhs)
		{
			return lhs - rhs < 0;
		}

		friend bool operator >(CIterator const& lhs, CIterator const& rhs)
		{
			return lhs - rhs > 0;
		}

		friend bool operator <=(CIterator const& lhs, CIterator const& rhs)
		{
			return !(lhs > rhs);
		}

		friend bool operator >=(CIterator const& lhs, CIterator const& rhs)
		{
			return !(lhs < rhs);
		}

		operator CIterator<const String, const Char>()const
		{
			return CIterator<const String, const Char>(m_str, m_index);
		}

	private:
		friend class CMyString;

		String * m_str;
		size_t m_index;

		CIterator(String * str, size_t index)
			:m_str(str)
			,m_index(index)
		{
		}
	};

public:
	typedef CIterator<CMyString, char> Iterator;
	typedef CIterator<const CMyString, const char> ConstIterator;

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

	Iterator begin()
	{
		return Iterator(this, 0);
	}

	ConstIterator begin()const
	{
		return ConstIterator(this, 0);
	}

	ConstIterator cbegin()const
	{
		return begin();
	}

	Iterator end()
	{
		return Iterator(this, m_length);
	}

	ConstIterator end()const
	{
		return ConstIterator(this, m_length);
	}

	ConstIterator cend()const
	{
		return end();
	}

	std::reverse_iterator<Iterator> rbegin()
	{
		return std::make_reverse_iterator(end());
	}

	std::reverse_iterator<ConstIterator> rbegin()const
	{
		return std::make_reverse_iterator(end());
	}

	std::reverse_iterator<ConstIterator> crbegin()const
	{
		return rbegin();
	}

	std::reverse_iterator<Iterator> rend()
	{
		return std::make_reverse_iterator(begin());
	}

	std::reverse_iterator<ConstIterator> rend()const
	{
		return std::make_reverse_iterator(begin());
	}

	std::reverse_iterator<ConstIterator> crend()const
	{
		return rend();
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
