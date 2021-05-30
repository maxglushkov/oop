#pragma once
#include <algorithm>
#include <stdexcept>

template<typename T>
class CMyArray
{
	template<typename Array, typename Item>
	class CIterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = Item;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type *;
		using reference = value_type &;

		CIterator & operator +=(difference_type offset)
		{
			const size_t newIndex = m_index + offset;
			if (newIndex > m_array->Size())
			{
				throw std::out_of_range("no iterator at requested position");
			}
			m_index = newIndex;
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
			if (lhs.m_array != rhs.m_array)
			{
				throw std::invalid_argument("no ordering is defined on iterators of different arrays");
			}
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
			return (*m_array)[m_index + offset];
		}

		reference operator *()const
		{
			return (*m_array)[m_index];
		}

		pointer operator ->()const
		{
			return &**this;
		}

		friend bool operator ==(CIterator const& lhs, CIterator const& rhs)
		{
			return lhs.m_array == rhs.m_array && lhs.m_index == rhs.m_index;
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

		operator CIterator<const Array, const Item>()const
		{
			return CIterator<const Array, const Item>(m_array, m_index);
		}

	private:
		friend class CMyArray;

		Array *m_array;
		size_t m_index;

		CIterator(Array *array, size_t index)
			:m_array(array)
			,m_index(index)
		{
		}
	};

public:
	typedef CIterator<CMyArray, T> Iterator;
	typedef CIterator<const CMyArray, const T> ConstIterator;

	CMyArray()
		:m_data(nullptr)
		,m_size(0)
	{
	}

	CMyArray(CMyArray const& other)
		:m_data(new T[other.m_size])
		,m_size(other.m_size)
	{
		try
		{
			std::copy(other.cbegin(), other.cend(), begin());
		}
		catch (...)
		{
			delete[] m_data;
			throw;
		}
	}

	CMyArray(CMyArray && other)
		:m_data(other.m_data)
		,m_size(other.m_size)
	{
		other.m_data = nullptr;
		other.m_size = 0;
	}

	template<typename FromT>
	CMyArray(CMyArray<FromT> const& other)
		:m_data(new T[other.Size()])
		,m_size(other.Size())
	{
		try
		{
			std::transform(
				other.cbegin(), other.cend(),
				begin(),
				[](FromT const& otherItem)
				{
					return static_cast<T>(otherItem);
				}
			);
		}
		catch (...)
		{
			delete[] m_data;
			throw;
		}
	}

	explicit CMyArray(size_t size)
		:m_data(new T[size])
		,m_size(size)
	{
	}

	~CMyArray()
	{
		delete[] m_data;
	}

	CMyArray & operator =(CMyArray const& other)
	{
		if (this == &other)
		{
			return *this;
		}
		return *this = CMyArray(other);
	}

	CMyArray & operator =(CMyArray && other)
	{
		if (this == &other)
		{
			return *this;
		}
		delete[] m_data;
		m_data = other.m_data;
		m_size = other.m_size;
		other.m_data = nullptr;
		other.m_size = 0;
		return *this;
	}

	template<typename FromT>
	CMyArray & operator =(CMyArray<FromT> const& other)
	{
		return *this = CMyArray(other);
	}

	T & operator [](size_t index)
	{
		if (index >= m_size)
		{
			ThrowIndexIsOutOfRange();
		}
		return m_data[index];
	}

	T const& operator [](size_t index)const
	{
		if (index >= m_size)
		{
			ThrowIndexIsOutOfRange();
		}
		return m_data[index];
	}

	void PushBack(T value)
	{
		Resize(m_size + 1);
		m_data[m_size - 1] = std::move(value);
	}

	size_t Size()const
	{
		return m_size;
	}

	void Resize(size_t newSize)
	{
		if (newSize == m_size)
		{
			return;
		}
		CMyArray resized(newSize);
		std::move(begin(), begin() + std::min(newSize, m_size), resized.begin());
		*this = std::move(resized);
	}

	void Clear()
	{
		delete[] m_data;
		m_data = nullptr;
		m_size = 0;
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
		return Iterator(this, m_size);
	}

	ConstIterator end()const
	{
		return ConstIterator(this, m_size);
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
	T *m_data;
	size_t m_size;

	static void ThrowIndexIsOutOfRange()
	{
		throw std::out_of_range("no item at requested index");
	}
};
