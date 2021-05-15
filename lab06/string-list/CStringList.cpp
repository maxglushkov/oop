#include <stdexcept>
#include "CStringList.h"

void CStringList::Clear()
{
	BasicItem * item = m_head.Next(BasicItem::Forward);
	while ((item = item->Next(BasicItem::Forward)))
	{
		delete (Item *)item->Prev(BasicItem::Forward);
	}
	m_head.Next(BasicItem::Forward) = &m_tail;
	m_tail.Prev(BasicItem::Forward) = &m_head;
	m_size = 0;
}

CStringList::Iterator CStringList::Insert(Iterator const& pos, std::string str)
{
	const BasicItem::IteratingDirection dir = pos.m_dir;
	BasicItem *const nextItem = pos.m_item;
	BasicItem *const prevItem = nextItem->Prev(dir);
	BasicItem *const newItem = new Item(dir, prevItem, nextItem, str);
	prevItem->Next(dir) = nextItem->Prev(dir) = newItem;
	++m_size;
	return Iterator(newItem, dir);
}

CStringList::Iterator CStringList::Erase(Iterator && pos)
{
	const BasicItem::IteratingDirection dir = pos.m_dir;
	if (BasicItem *const nextItem = pos.m_item->Next(dir))
	{
		BasicItem *const prevItem = pos.m_item->Prev(dir);
		prevItem->Next(dir) = nextItem;
		nextItem->Prev(dir) = prevItem;
		--m_size;
		delete (Item *)pos.m_item;
		pos.m_item = nextItem;
		return pos;
	}
	NotDereferencableIterator();
}

void CStringList::NotIncrementableIterator()
{
	throw std::invalid_argument("list iterator is not incrementable");
}

void CStringList::NotDecrementableIterator()
{
	throw std::invalid_argument("list iterator is not decrementable");
}

void CStringList::NotDereferencableIterator()
{
	throw std::invalid_argument("list iterator is not dereferencable");
}
