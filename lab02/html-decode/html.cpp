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
		beginPos = endPos + 1;

		const string_view entity(html.data() + beginPos, html.size() - beginPos);
		char decoded;
		if (size_t entitySize = DecodeHtmlEntity(entity, decoded))
		{
			text.push_back(decoded);
			beginPos += entitySize;
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
