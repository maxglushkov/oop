#pragma once
#include <string>

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	// выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP)
		:m_domain(domain)
		,m_document(NormalizeDocumentPart(document))
		,m_protocol(protocol)
		,m_port(DefaultPortForProtocol(protocol))
	{
	}

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port)
		:m_domain(domain)
		,m_document(NormalizeDocumentPart(document))
		,m_protocol(protocol)
		,m_port(port)
	{
		// Throw an exception if protocol is not valid
		DefaultPortForProtocol(protocol);
	}

	// возвращает строковое представление URL-а. Порт, являющийся стандартным для
	// выбранного протокола (80 для http и 443 для https) в эту строку
	// не должен включаться
	std::string GetURL()const;

	// возвращает доменное имя
	std::string GetDomain()const
	{
		return m_domain;
	}

	/*
		Возвращает имя документа. Примеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument()const
	{
		return m_document;
	}

	// возвращает тип протокола
	Protocol GetProtocol()const
	{
		return m_protocol;
	}

	// возвращает номер порта
	unsigned short GetPort()const
	{
		return m_port;
	}

private:
	constexpr static char SCHEME_SEPARATOR[] = "://";
	constexpr static char PORT_SEPARATOR = ':';
	constexpr static char DOCUMENT_SEPARATOR = '/';

	std::string m_domain, m_document;
	Protocol m_protocol;
	unsigned short m_port;

	static std::string NormalizeDocumentPart(std::string_view const& document)
	{
		std::string normalized;
		if (document.empty() ? true : document[0] != DOCUMENT_SEPARATOR)
		{
			normalized.push_back(DOCUMENT_SEPARATOR);
		}
		return normalized.append(document);
	}

	static unsigned short DefaultPortForProtocol(Protocol protocol);
};

std::ostream & operator <<(std::ostream & output, CHttpUrl::Protocol protocol);
