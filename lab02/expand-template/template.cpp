#include <iostream>
#include "template.h"
#include "trie.h"
using std::string;

string ExpandTemplate(string const& tpl, std::map<string, string> const& params, Trie const& trie);

string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	return ExpandTemplate(tpl, params, Trie::FromMapKeys(params));
}

bool ExpandTemplateStream(std::istream & input, std::ostream & output, std::map<std::string, std::string> const& params)
{
	const Trie trie = Trie::FromMapKeys(params);

	string line;
	while (std::getline(input, line))
	{
		output << ExpandTemplate(line, params, trie);
		if (!output)
		{
			return false;
		}

		if (input.eof())
		{
			return true;
		}

		output << '\n';
		if (!output)
		{
			return false;
		}
	}
	return input.eof() ? bool(output.flush()) : false;
}

string ExpandTemplate(string const& tpl, std::map<string, string> const& params, Trie const& trie)
{
	string expanded;

	string::size_type processedPos = 0;
	for (auto const& [beginPos, length]: trie.FindLongestMatches(tpl))
	{
		if (beginPos >= processedPos)
		{
			expanded.append(tpl, processedPos, beginPos - processedPos);
			expanded.append(params.at(tpl.substr(beginPos, length)));
			processedPos = beginPos + length;
		}
	}
	expanded.append(tpl, processedPos);
	return expanded;
}
