#include <stdexcept>
#include "CStringList.h"

CStringList::Iterator CStringList::Insert(Iterator const& pos, std::string str)
{
	BasicItem *const nextItem = pos.m_item;
	BasicItem *const prevItem = nextItem->m_prev;
	BasicItem *const newItem = new Item{{prevItem, nextItem}, std::move(str)};
	prevItem->m_next = nextItem->m_prev = newItem;
	++m_size;
	return newItem;
}

CStringList::Iterator CStringList::Erase(Iterator const& pos)
{
	if (BasicItem *const nextItem = pos.m_item->m_next)
	{
		BasicItem *const prevItem = pos.m_item->m_prev;
		prevItem->m_next = nextItem;
		nextItem->m_prev = prevItem;
		--m_size;
		delete static_cast<Item *>(pos.m_item);
		return nextItem;
	}
	ThrowNotDereferencableIterator();
}

void CStringList::ThrowNotIncrementableIterator()
{
	throw std::invalid_argument("list iterator is not incrementable");
}

void CStringList::ThrowNotDecrementableIterator()
{
	throw std::invalid_argument("list iterator is not decrementable");
}

void CStringList::ThrowNotDereferencableIterator()
{
	throw std::invalid_argument("list iterator is not dereferencable");
}

void CStringList::Initialize(CStringList const& source)
{
	m_head.m_prev = nullptr;
	BasicItem *prevItem = &m_head;
	try
	{
		const BasicItem *nextSourceItem = source.m_head.m_next;
		while ((nextSourceItem = nextSourceItem->m_next))
		{
			prevItem = prevItem->m_next = new Item{
				{prevItem, nullptr},
				static_cast<Item *>(nextSourceItem->m_prev)->m_value
			};
		}
	}
	catch(...)
	{
		while ((prevItem = prevItem->m_prev))
		{
			delete static_cast<Item *>(prevItem->m_next);
		}
		throw;
	}
	prevItem->m_next = &m_tail;
	m_tail = {prevItem, nullptr};
	m_size = source.m_size;
}

void CStringList::Cleanup()
{
	BasicItem *item = m_head.m_next;
	while ((item = item->m_next))
	{
		delete static_cast<Item *>(item->m_prev);
	}
}
