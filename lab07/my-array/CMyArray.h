#pragma once
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

	explicit CMyArray(size_t capacity = 0)
	{
		if (!capacity)
		{
			m_data = nullptr;
		}
		else
		{
			m_data = static_cast<T *>(malloc(capacity * sizeof(T)));
			if (!m_data)
			{
				throw std::bad_alloc();
			}
		}
		m_size = 0;
		m_capacity = capacity;
	}

	CMyArray(CMyArray && other)
	{
		Initialize(std::move(other));
	}

	CMyArray(CMyArray const& other)
		:CMyArray(other.Capacity())
	{
		try
		{
			for (T const& item: other)
			{
				new (m_data + m_size) T(item);
				++m_size;
			}
		}
		catch (...)
		{
			Destroy(0, m_size);
			free(m_data);
			throw;
		}
	}

	template<typename FromT>
	CMyArray(CMyArray<FromT> const& other)
		:CMyArray(other.Capacity())
	{
		try
		{
			for (FromT const& item: other)
			{
				new (m_data + m_size) T(static_cast<T>(item));
				++m_size;
			}
		}
		catch (...)
		{
			Destroy(0, m_size);
			free(m_data);
			throw;
		}
	}

	~CMyArray()
	{
		Destroy(0, m_size);
		free(m_data);
	}

	CMyArray & operator =(CMyArray && other)
	{
		if (this != &other)
		{
			Destroy(0, m_size);
			free(m_data);
			Initialize(std::move(other));
		}
		return *this;
	}

	CMyArray & operator =(CMyArray const& other)
	{
		if (this != &other)
		{
			*this = CMyArray(other);
		}
		return *this;
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
		if (m_size == m_capacity)
		{
			Reserve(m_capacity ? m_capacity * 2 : 1);
		}
		new (m_data + m_size) T(std::move(value));
		++m_size;
	}

	size_t Size()const
	{
		return m_size;
	}

	size_t Capacity()const
	{
		return m_capacity;
	}

	void Resize(size_t newSize)
	{
		if (newSize > m_capacity)
		{
			Reserve(newSize);
		}

		if (newSize < m_size)
		{
			Destroy(newSize, m_size);
		}
		else if (newSize > m_size)
		{
			size_t size = m_size;
			try
			{
				while (size != newSize)
				{
					new (m_data + size) T();
					++size;
				}
			}
			catch (...)
			{
				Destroy(m_size, size);
				throw;
			}
		}
		m_size = newSize;
	}

	void Reserve(size_t newCapacity)
	{
		if (newCapacity <= m_capacity)
		{
			return;
		}

		CMyArray reserved(newCapacity);
		for (T & item: *this)
		{
			new (reserved.m_data + reserved.m_size) T(std::move(item));
			++reserved.m_size;
		}
		*this = std::move(reserved);
	}

	void Clear()
	{
		Destroy(0, m_size);
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
	size_t m_size, m_capacity;

	static void ThrowIndexIsOutOfRange()
	{
		throw std::out_of_range("no item at requested index");
	}

	void Initialize(CMyArray && other)
	{
		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	void Destroy(size_t begin, size_t end)
	{
		while (begin != end)
		{
			m_data[begin].~T();
			++begin;
		}
	}
};
