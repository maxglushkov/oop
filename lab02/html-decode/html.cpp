#include "html.h"
#include "html-entity.h"
using std::string, std::string_view;

string HtmlDecode(std::string const& html)
{
	string text;
	string::size_type beginPos = 0, endPos;
	while ((endPos = html.find('&', beginPos)) != string::npos)
	{
		text.append(html, beginPos, endPos - beginPos);
		beginPos = endPos;

		endPos = html.find(';', beginPos);
		if (endPos == string::npos)
		{
			break;
		}
		++beginPos;

		const string_view entity(html.data() + beginPos, endPos - beginPos);
		if (const char decoded = DecodeHtmlEntity(entity))
		{
			text.push_back(decoded);
			beginPos = endPos + 1;
		}
		else
		{
			text.push_back('&');
		}
	}
	text.append(html, beginPos);
	return text;
}

bool HtmlDecodeStream(std::istream & input, std::ostream & output)
{
	string line;
	while (std::getline(input, line))
	{
		output << HtmlDecode(line);
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
	return input.eof();
}
