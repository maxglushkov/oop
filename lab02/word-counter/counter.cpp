#include "counter.h"

bool CountWords(std::istream & input, WordCounts & wordCounts)
{
	std::string word;
	while (input >> word)
	{
		if (!word.empty())
		{
			++wordCounts[word];
		}
	}
	return input.eof();
}
