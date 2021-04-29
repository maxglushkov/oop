#include "trie.h"

Trie Trie::FromMapKeys(std::map<std::string, std::string> const& map)
{
	Trie trie;
	for (auto item: map)
	{
		trie.Append(item.first);
	}
	trie.UpdateSuffixLinks();
	return trie;
}

std::map<Trie::size_type, Trie::size_type> Trie::FindLongestMatches(std::string const& str)const
{
	std::map<size_type, size_type> matches;

	const Node *node = m_root;
	for (size_type pos = 0; pos < str.length();)
	{
		const char c = str[pos++];

		for (const Node *n = node->firstChild;;)
		{
			const char cmp = CompareNode(n, c);
			if (cmp > 0)
			{
				if (!node->suffixLink)
				{
					break;
				}
				node = node->suffixLink;
				n = node->firstChild;
				continue;
			}
			if (cmp == 0)
			{
				for (node = n; n ? n->length : false; n = n->suffixLink)
				{
					matches[pos - n->length] = n->length;
				}
				break;
			}
			n = n->nextSibling;
		}
	}

	return matches;
}

void Trie::Append(std::string const& str)
{
	Node **node = &m_root;
	for (const char c: str)
	{
		for (node = &(*node)->firstChild;; node = &(*node)->nextSibling)
		{
			const char cmp = CompareNode(*node, c);
			if (cmp > 0)
			{
				Node *newNode = new Node{};
				newNode->value = c;
				newNode->nextSibling = *node;
				*node = newNode;
			}
			if (cmp >= 0)
			{
				break;
			}
		}
	}
	(*node)->length = str.length();
}

void Trie::UpdateSuffixLinks()
{
	for (Node *node = m_root->firstChild; node; node = node->nextSibling)
	{
		node->suffixLink = m_root;
		UpdateSuffixLinksOnLine(node->firstChild);
	}
}

void Trie::UpdateSuffixLinksOnLine(Node *from)
{
	const Node *to = m_root->firstChild;
	for (; from; from = from->nextSibling)
	{
		if (from->suffixLink)
		{
			continue;
		}

		while (CompareNode(to, from->value) < 0)
		{
			to = to->nextSibling;
		}
		if (CompareNode(to, from->value) == 0)
		{
			CreateSuffixLink(from, to);
		}
		else
		{
			from->suffixLink = m_root;
		}

		UpdateSuffixLinksOnLine(from->firstChild);
	}
}

void Trie::CreateSuffixLink(Node *from, const Node *to)
{
	from->suffixLink = to;
	if (!from->length)
	{
		from->length = to->length;
	}

	from = from->firstChild;
	to = to->firstChild;
	while (from && to)
	{
		const char cmp = from->value - to->value;
		if (cmp == 0)
		{
			CreateSuffixLink(from, to);
		}
		if (cmp <= 0)
		{
			from = from->nextSibling;
		}
		if (cmp >= 0)
		{
			to = to->nextSibling;
		}
	}
}
