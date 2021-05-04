#include <iostream>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
using std::cerr, std::cout;

void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	std::string line;
	while (cout << "> " && std::getline(std::cin, line))
	{
		try
		{
			CHttpUrl url = line;
			cout << "URL: " << url.GetURL() << '\n';
			cout << "Protocol: " << url.GetProtocol() << '\n';
			cout << "Domain: " << url.GetDomain() << '\n';
			cout << "Port: " << url.GetPort() << '\n';
			cout << "Document: " << url.GetDocument() << '\n';
		}
		catch (CUrlParsingError const& e)
		{
			cerr << "Error: " << e.what() << '\n';
		}
	}
	return 0;
}

void PrintUsage(const char *programName)
{
	cerr << "Usage: " << programName << '\n';
	cerr << "Reads URLs from standard input and prints information about them in standard output.\n";
}
