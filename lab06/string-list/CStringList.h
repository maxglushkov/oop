#pragma once
#include <string>

class CStringList
{
	struct BasicItem
	{
		enum IteratingDirection
		{
			Forward = 0,
			Backward = 1
		};

		BasicItem(IteratingDirection dir, BasicItem * prev, BasicItem * next)
		{
			Prev(dir) = prev;
			Next(dir) = next;
		}

		BasicItem *& Next(IteratingDirection dir)
		{
			return m_links[dir ^ Forward];
		}

		const BasicItem * Next(IteratingDirection dir)const
		{
			return m_links[dir ^ Forward];
		}

		BasicItem *& Prev(IteratingDirection dir)
		{
			return m_links[dir ^ Backward];
		}

		const BasicItem * Prev(IteratingDirection dir)const
		{
			return m_links[dir ^ Backward];
		}

	private:
		BasicItem * m_links[2];
	};

	struct Item: public BasicItem
	{
		std::string m_value;

		Item(IteratingDirection dir, BasicItem * prev, BasicItem * next, std::string value)
			:BasicItem(dir, prev, next)
			,m_value(value)
		{
		}
	};

	template<typename T, typename BasicItem, typename ItemPointer>
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
			if (BasicItem *const nextItem = m_item->Next(m_dir))
			{
				m_item = nextItem;
				return *this;
			}
			NotIncrementableIterator();
		}

		CIterator operator ++(int)
		{
			if (BasicItem *const nextItem = m_item->Next(m_dir))
			{
				CIterator saved = *this;
				m_item = nextItem;
				return saved;
			}
			NotIncrementableIterator();
		}

		CIterator & operator --()
		{
			if (BasicItem *const prevItem = m_item->Prev(m_dir))
			{
				if (prevItem->Prev(m_dir))
				{
					m_item = prevItem;
					return *this;
				}
			}
			NotDecrementableIterator();
		}

		CIterator operator --(int)
		{
			if (BasicItem *const prevItem = m_item->Prev(m_dir))
			{
				if (prevItem->Prev(m_dir))
				{
					CIterator saved = *this;
					m_item = prevItem;
					return saved;
				}
			}
			NotDecrementableIterator();
		}

		reference operator *()const
		{
			if (m_item->Next(BasicItem::Forward) && m_item->Prev(BasicItem::Forward))
			{
				return ItemPointer(m_item)->m_value;
			}
			NotDereferencableIterator();
		}

		pointer operator ->()const
		{
			return &**this;
		}

		bool operator ==(CIterator const& other)const
		{
			return m_dir == other.m_dir && m_item == other.m_item;
		}

		bool operator !=(CIterator const& other)const
		{
			return !(*this == other);
		}

	private:
		friend class CStringList;

		typename BasicItem::IteratingDirection m_dir;
		BasicItem * m_item;

		CIterator(BasicItem * item, typename BasicItem::IteratingDirection dir)
			:m_dir(dir)
			,m_item(item)
		{
		}
	};

public:
	using Iterator = CIterator<std::string, BasicItem, Item *>;
	using ConstIterator = CIterator<const std::string, const BasicItem, const Item *>;

	CStringList()
		:m_head(BasicItem::Forward, nullptr, &m_tail)
		,m_tail(BasicItem::Forward, &m_head, nullptr)
		,m_size(0)
	{
	}

	~CStringList()
	{
		Clear();
	}

	void PushFront(std::string str)
	{
		Insert(rend(), str);
	}

	void PushBack(std::string str)
	{
		Insert(end(), str);
	}

	size_t Size()const
	{
		return m_size;
	}

	bool IsEmpty()const
	{
		return m_size == 0;
	}

	void Clear();

	Iterator Insert(Iterator const& pos, std::string str);

	Iterator Erase(Iterator && pos);

	Iterator begin()
	{
		return Iterator(m_head.Next(BasicItem::Forward), BasicItem::Forward);
	}

	ConstIterator begin()const
	{
		return ConstIterator(m_head.Next(BasicItem::Forward), BasicItem::Forward);
	}

	ConstIterator cbegin()const
	{
		return begin();
	}

	Iterator end()
	{
		return Iterator(&m_tail, BasicItem::Forward);
	}

	ConstIterator end()const
	{
		return ConstIterator(&m_tail, BasicItem::Forward);
	}

	ConstIterator cend()const
	{
		return end();
	}

	Iterator rbegin()
	{
		return Iterator(m_tail.Next(BasicItem::Backward), BasicItem::Backward);
	}

	ConstIterator rbegin()const
	{
		return ConstIterator(m_tail.Next(BasicItem::Backward), BasicItem::Backward);
	}

	ConstIterator crbegin()const
	{
		return rbegin();
	}

	Iterator rend()
	{
		return Iterator(&m_head, BasicItem::Backward);
	}

	ConstIterator rend()const
	{
		return ConstIterator(&m_head, BasicItem::Backward);
	}

	ConstIterator crend()const
	{
		return rend();
	}

private:
	BasicItem m_head, m_tail;
	size_t m_size;

	[[noreturn]] static void NotIncrementableIterator();

	[[noreturn]] static void NotDecrementableIterator();

	[[noreturn]] static void NotDereferencableIterator();
};
