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

	bool operator <(string_view const& other)const
	{
		return m_html < other;
	}
};

constexpr std::array<HtmlToText, 5> SORTED_ENTITIES =
{
	HtmlToText("amp"sv, '&'),
	HtmlToText("apos"sv, '\''),
	HtmlToText("gt"sv, '>'),
	HtmlToText("lt"sv, '<'),
	HtmlToText("quot"sv, '"')
};

char DecodeHtmlEntity(std::string_view const& entity)
{
	const auto && iter = std::lower_bound(SORTED_ENTITIES.begin(), SORTED_ENTITIES.end(), entity);

	if (iter != SORTED_ENTITIES.end())
	{
		if (iter->m_html == entity)
		{
			return iter->m_text;
		}
	}
	return 0;
}
