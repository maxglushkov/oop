#include "html.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"html-decode"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	HtmlDecodeStream(std::cin, std::cout);

	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName)
	{
		programName = "html-decode";
	}
	cerr << "Usage: " << programName << '\n';
	cerr << "Decodes html-encoded text from standard input to standard output.\n";
}
