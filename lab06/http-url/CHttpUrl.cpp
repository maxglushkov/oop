#include <sstream>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
using std::string, std::string_view;

constexpr char HTTP_SCHEME[] = "http";
constexpr char HTTPS_SCHEME[] = "https";
constexpr uint32_t MAX_PORT = 0xffff;

CHttpUrl::Protocol ParseScheme(string_view const& scheme);

unsigned short ParsePort(string_view const& port);

CHttpUrl::CHttpUrl(std::string const& url)
{
	const string::size_type schemeEndPos = url.find(SCHEME_SEPARATOR);
	if (schemeEndPos == string::npos)
	{
		throw CUrlParsingError("scheme separator \"://\" was not found");
	}
	m_protocol = ParseScheme(string_view(url.data(), schemeEndPos));

	const string::size_type domainBeginPos = schemeEndPos + sizeof SCHEME_SEPARATOR - 1;
	const string::size_type documentBeginPos = std::min(url.find(DOCUMENT_SEPARATOR, domainBeginPos), url.length());
	m_document = NormalizeDocumentPart(string_view(url.data() + documentBeginPos, url.length() - documentBeginPos));

	string::size_type domainEndPos = url.rfind(PORT_SEPARATOR, documentBeginPos);
	if (domainEndPos == schemeEndPos)
	{
		domainEndPos = documentBeginPos;
		m_port = DefaultPortForProtocol(m_protocol);
	}
	else
	{
		const string::size_type portBeginPos = domainEndPos + 1;
		m_port = ParsePort(string_view(url.data() + portBeginPos, documentBeginPos - portBeginPos));
	}

	m_domain = url.substr(domainBeginPos, domainEndPos - domainBeginPos);
}

std::string CHttpUrl::GetURL()const
{
	std::ostringstream url;
	url << m_protocol << SCHEME_SEPARATOR << m_domain;
	if (m_port != DefaultPortForProtocol(m_protocol))
	{
		url << PORT_SEPARATOR << m_port;
	}
	url << m_document;
	return url.str();
}

unsigned short CHttpUrl::DefaultPortForProtocol(Protocol protocol)
{
	switch (protocol)
	{
		case Protocol::HTTP:
			return 80;
		case Protocol::HTTPS:
			return 443;
		default:
			throw std::invalid_argument("unknown protocol");
	}
}

std::ostream & operator <<(std::ostream & output, CHttpUrl::Protocol protocol)
{
	switch (protocol)
	{
		case CHttpUrl::Protocol::HTTP:
			output << HTTP_SCHEME;
			break;
		case CHttpUrl::Protocol::HTTPS:
			output << HTTPS_SCHEME;
	}
	return output;
}

CHttpUrl::Protocol ParseScheme(string_view const& scheme)
{
	if (scheme == HTTP_SCHEME)
	{
		return CHttpUrl::Protocol::HTTP;
	}
	if (scheme == HTTPS_SCHEME)
	{
		return CHttpUrl::Protocol::HTTPS;
	}
	throw CUrlParsingError("unknown URL scheme");
}

unsigned short ParsePort(string_view const& port)
{
	auto iter = port.begin();
	if (iter == port.end())
	{
		throw CUrlParsingError("port number should contain at least 1 digit");
	}

	uint32_t number = 0;
	do
	{
		signed char digit = *iter - '0';
		if (digit < 0 || digit >= 10)
		{
			throw CUrlParsingError("port number should contain only digits");
		}

		number = number * 10 + digit;
		if (number > MAX_PORT)
		{
			throw CUrlParsingError("port number should not be greater then 65535");
		}
	}
	while (++iter != port.end());

	return number;
}
