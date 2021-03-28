#include <iostream>
#include "counter.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"word-counter"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	WordCounts wordCounts;
	CountWords(std::cin, wordCounts);

	for (auto & [word, count]: wordCounts)
	{
		std::cout << word << ": " << count << '\n';
	}
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName)
	{
		programName = "word-counter";
	}
	cerr << "Usage: " << programName << '\n';
	cerr << "Counts word frequencies from standard input.\n";
}
