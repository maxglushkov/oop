#include <algorithm>
#include "html-entity.h"
using namespace std::literals;

constexpr std::array<std::pair<std::string_view, char>, 5> SORTED_ENTITIES =
{
	make_pair("&amp"sv, '&'),
	make_pair("&apos"sv, '\''),
	make_pair("&gt"sv, '>'),
	make_pair("&lt"sv, '<'),
	make_pair("&quot"sv, '"')
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

	if (iter != SORTED_ENTITIES.end())
	{
		decoded = iter->second;

		const size_t semicolonPos = iter->first.size();
		if (semicolonPos < entity.size())
		{
			if (entity[semicolonPos] == ';') return semicolonPos + 1;
		}
		return semicolonPos;
	}
	return 0;
}
