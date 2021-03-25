#include <algorithm>
#include <array>
#include "html-entity.h"
using namespace std::literals;
using std::string_view;

struct HtmlToText
{
	const string_view m_html;
	const char m_text;

	constexpr HtmlToText(string_view const& html, const char text)
		:m_html(html)
		,m_text(text)
	{
	}
};

bool operator <(string_view const& lhs, HtmlToText const& rhs)
{
	return lhs < rhs.m_html;
}

constexpr std::array<HtmlToText, 5> SORTED_ENTITIES =
{
	HtmlToText("amp"sv, '&'),
	HtmlToText("apos"sv, '\''),
	HtmlToText("gt"sv, '>'),
	HtmlToText("lt"sv, '<'),
	HtmlToText("quot"sv, '"')
};

size_t DecodeHtmlEntity(std::string_view const& entity, char & decoded)
{
	auto && iter = std::upper_bound(SORTED_ENTITIES.begin(), SORTED_ENTITIES.end(), entity);

	if (iter != SORTED_ENTITIES.begin())
	{
		--iter;

		const size_t entitySize = iter->m_html.size();
		if (entity.compare(0, entitySize, iter->m_html) == 0)
		{
			decoded = iter->m_text;

			if (entitySize < entity.size())
			{
				if (entity[entitySize] == ';') return entitySize + 1;
			}
			return entitySize;
		}
	}
	return 0;
}
