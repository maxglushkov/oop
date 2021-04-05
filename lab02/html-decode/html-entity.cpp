#include <algorithm>
#include "html-entity.h"
using namespace std::literals;
using std::pair;

constexpr std::array<std::pair<std::string_view, char>, 5> SORTED_ENTITIES =
{
	pair("&amp;"sv, '&'),
	pair("&apos;"sv, '\''),
	pair("&gt;"sv, '>'),
	pair("&lt;"sv, '<'),
	pair("&quot;"sv, '"')
};

size_t DecodeHtmlEntity(std::string_view const& entity, char & decoded)
{
	const auto iter = std::find_if(
		SORTED_ENTITIES.begin(), SORTED_ENTITIES.end(),
		[&entity](const auto & pair)
		{
			return entity.compare(0, pair.first.size(), pair.first) == 0;
		}
	);
	if (iter == SORTED_ENTITIES.end())
	{
		return 0;
	}
	decoded = iter->second;
	return iter->first.size();
}
