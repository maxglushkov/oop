#pragma once
#include <string>

class CStringList
{
	struct BasicItem
	{
		BasicItem *m_prev, *m_next;
	};

	struct Item: public BasicItem
	{
		std::string m_value;
	};

	template<typename T, typename BasicItem, typename Item>
	class CIterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type *;
		using reference = value_type &;

		CIterator & operator ++()
		{
			if (BasicItem *const nextItem = m_item->m_next)
			{
				m_item = nextItem;
				return *this;
			}
			ThrowNotIncrementableIterator();
		}

		CIterator operator ++(int)
		{
			if (BasicItem *const nextItem = m_item->m_next)
			{
				CIterator saved = *this;
				m_item = nextItem;
				return saved;
			}
			ThrowNotIncrementableIterator();
		}

		CIterator & operator --()
		{
			if (BasicItem *const prevItem = m_item->m_prev)
			{
				if (prevItem->m_prev)
				{
					m_item = prevItem;
					return *this;
				}
			}
			ThrowNotDecrementableIterator();
		}

		CIterator operator --(int)
		{
			if (BasicItem *const prevItem = m_item->m_prev)
			{
				if (prevItem->m_prev)
				{
					CIterator saved = *this;
					m_item = prevItem;
					return saved;
				}
			}
			ThrowNotDecrementableIterator();
		}

		reference operator *()const
		{
			if (m_item->m_prev && m_item->m_next)
			{
				return static_cast<Item *>(m_item)->m_value;
			}
			ThrowNotDereferencableIterator();
		}

		pointer operator ->()const
		{
			return &**this;
		}

		friend bool operator ==(CIterator const& lhs, CIterator const& rhs)
		{
			return lhs.m_item == rhs.m_item;
		}

		friend bool operator !=(CIterator const& lhs, CIterator const& rhs)
		{
			return !(lhs == rhs);
		}

		operator CIterator<const T, const BasicItem, const Item>()const
		{
			return m_item;
		}

	private:
		friend class CStringList;

		BasicItem *m_item;

		CIterator(BasicItem *item)
			:m_item(item)
		{
		}
	};

public:
	using Iterator = CIterator<std::string, BasicItem, Item>;
	using ConstIterator = CIterator<const std::string, const BasicItem, const Item>;

	CStringList()
	{
		Initialize();
	}

	CStringList(CStringList const& other)
	{
		Initialize(other);
	}

	CStringList(CStringList && other)
	{
		Initialize(std::move(other));
	}

	~CStringList()
	{
		Cleanup();
	}

	CStringList & operator =(CStringList const& other)
	{
		return *this = CStringList(other);
	}

	CStringList & operator =(CStringList && other)
	{
		Cleanup();
		Initialize(std::move(other));
		return *this;
	}

	void PushFront(std::string str)
	{
		Insert(begin(), std::move(str));
	}

	void PushBack(std::string str)
	{
		Insert(end(), std::move(str));
	}

	size_t Size()const
	{
		return m_size;
	}

	bool IsEmpty()const
	{
		return m_size == 0;
	}

	void Clear()
	{
		Cleanup();
		Initialize();
	}

	Iterator Insert(Iterator const& pos, std::string str);

	Iterator Erase(Iterator const& pos);

	Iterator begin()
	{
		return m_head.m_next;
	}

	ConstIterator begin()const
	{
		return m_head.m_next;
	}

	ConstIterator cbegin()const
	{
		return begin();
	}

	Iterator end()
	{
		return &m_tail;
	}

	ConstIterator end()const
	{
		return &m_tail;
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
	BasicItem m_head, m_tail;
	size_t m_size;

	[[noreturn]] static void ThrowNotIncrementableIterator();

	[[noreturn]] static void ThrowNotDecrementableIterator();

	[[noreturn]] static void ThrowNotDereferencableIterator();

	void Initialize()
	{
		m_head = {nullptr, &m_tail};
		m_tail = {&m_head, nullptr};
		m_size = 0;
	}

	void Initialize(CStringList const& source);

	void Initialize(CStringList && source)
	{
		m_head.m_prev = nullptr;
		(m_head.m_next = source.m_head.m_next)->m_prev = &m_head;
		(m_tail.m_prev = source.m_tail.m_prev)->m_next = &m_tail;
		m_tail.m_next = nullptr;
		m_size = source.m_size;
		source.Initialize();
	}

	void Cleanup();
};
