#pragma once
#include <map>
#include <string>

class Trie
{
public:
	typedef std::string::size_type size_type;

	Trie()
		:m_root(new Node{})
	{
	}

	Trie(Trie && other)
		:m_root(other.m_root)
	{
		new (&other) Trie();
	}

	Trie(const Trie &) = delete;

	~Trie()
	{
		ForEachChildSiblingNode(m_root, [](Node *node){
			delete node;
		});
	}

	Trie & operator =(Trie &&) = delete;
	Trie & operator =(const Trie &) = delete;

	static Trie FromMapKeys(std::map<std::string, std::string> const& map);

	std::map<size_type, size_type> FindLongestMatches(std::string const& str)const;

private:
	struct Node
	{
		char value;
		size_type length;
		Node *firstChild, *nextSibling;
		const Node *suffixLink;
	};

	Node *m_root;

	void Append(std::string const& str);

	void UpdateSuffixLinks();

	void UpdateSuffixLinksOnLine(Node *from);

	static void CreateSuffixLink(Node *from, const Node *to);

	static void ForEachChildSiblingNode(Node *node, void (*func)(Node *node))
	{
		if (node)
		{
			ForEachChildSiblingNode(node->firstChild, func);
			ForEachChildSiblingNode(node->nextSibling, func);
			func(node);
		}
	}

	static char CompareNode(const Node *node, char value)
	{
		if (!node)
		{
			return 1;
		}
		return node->value - value;
	}
};
