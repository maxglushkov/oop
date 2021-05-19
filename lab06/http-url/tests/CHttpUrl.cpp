#include <catch2/catch.hpp>
#include "../CHttpUrl.h"
using namespace std::literals;

TEST_CASE("Checking whether URLs can be parsed")
{
	CHttpUrl url = "http://localhost:8080"s;
	REQUIRE(url.GetURL() == "http://localhost:8080/");
	REQUIRE(url.GetDomain() == "localhost");
	REQUIRE(url.GetDocument() == "/");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetPort() == 8080);

	url = "https://example.com:443/?ssl=false"s;
	REQUIRE(url.GetURL() == "https://example.com/?ssl=false");
	REQUIRE(url.GetDomain() == "example.com");
	REQUIRE(url.GetDocument() == "/?ssl=false");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetPort() == 443);

	url = "http://root:toor@localhost.local:443/"s;
	REQUIRE(url.GetURL() == "http://root:toor@localhost.local:443/");
	REQUIRE(url.GetDomain() == "root:toor@localhost.local");
	REQUIRE(url.GetDocument() == "/");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetPort() == 443);

	url = "http://example.com"s;
	REQUIRE(url.GetURL() == "http://example.com/");
	REQUIRE(url.GetDomain() == "example.com");
	REQUIRE(url.GetDocument() == "/");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetPort() == 80);
}

TEST_CASE("Checking whether URLs can be composed from parts")
{
	CHttpUrl url("", "");
	REQUIRE(url.GetURL() == "http:///");
	REQUIRE(url.GetDomain() == "");
	REQUIRE(url.GetDocument() == "/");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetPort() == 80);

	url = CHttpUrl("localhost", "/");
	REQUIRE(url.GetURL() == "http://localhost/");
	REQUIRE(url.GetDomain() == "localhost");
	REQUIRE(url.GetDocument() == "/");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetPort() == 80);

	url = CHttpUrl("example.com", "download", CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetURL() == "https://example.com/download");
	REQUIRE(url.GetDomain() == "example.com");
	REQUIRE(url.GetDocument() == "/download");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetPort() == 443);

	url = CHttpUrl("localhost", "#", CHttpUrl::Protocol::HTTPS, 8443);
	REQUIRE(url.GetURL() == "https://localhost:8443/#");
	REQUIRE(url.GetDomain() == "localhost");
	REQUIRE(url.GetDocument() == "/#");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	REQUIRE(url.GetPort() == 8443);

	url = CHttpUrl("example.com", "?https=true", CHttpUrl::Protocol::HTTP, 80);
	REQUIRE(url.GetURL() == "http://example.com/?https=true");
	REQUIRE(url.GetDomain() == "example.com");
	REQUIRE(url.GetDocument() == "/?https=true");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetPort() == 80);

	url = CHttpUrl("", "/", CHttpUrl::Protocol::HTTP, 8080);
	REQUIRE(url.GetURL() == "http://:8080/");
	REQUIRE(url.GetDomain() == "");
	REQUIRE(url.GetDocument() == "/");
	REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
	REQUIRE(url.GetPort() == 8080);
}

TEST_CASE("Checking how invalid URLs are processed")
{
	REQUIRE_THROWS(CHttpUrl("htt://localhost/download"));
	REQUIRE_THROWS(CHttpUrl("httpd://localhost/download"));
	REQUIRE_NOTHROW(CHttpUrl("http://localhost/download"));

	REQUIRE_THROWS(CHttpUrl("http:/example.com"));
	REQUIRE_THROWS(CHttpUrl("//example.com"));
	REQUIRE_NOTHROW(CHttpUrl("http://example.com"));

	REQUIRE_THROWS(CHttpUrl("http://example.com:"));
	REQUIRE_THROWS(CHttpUrl("http://example.com:-1"));
	REQUIRE_THROWS(CHttpUrl("http://example.com:+1"));
	REQUIRE_THROWS(CHttpUrl("http://example.com:0x16"));
	REQUIRE_NOTHROW(CHttpUrl("HttP://example.com:1"));

	REQUIRE_THROWS(CHttpUrl("https://example.com:0"));
	REQUIRE_THROWS(CHttpUrl("https://example.com:65536"));
	REQUIRE_NOTHROW(CHttpUrl("htTpS://example.com:65535"));

	REQUIRE_THROWS(CHttpUrl("https://root:toor@localhost/"));
	REQUIRE_NOTHROW(CHttpUrl("https://root:toor@localhost:443/"));

	REQUIRE_THROWS(CHttpUrl("localhost", "/", CHttpUrl::Protocol(2)));
	REQUIRE_THROWS(CHttpUrl("localhost", "/", CHttpUrl::Protocol(-1)));
	REQUIRE_THROWS(CHttpUrl("localhost", "/", CHttpUrl::Protocol(2)), 22);
	REQUIRE_THROWS(CHttpUrl("localhost", "/", CHttpUrl::Protocol(-1)), 22);
}
