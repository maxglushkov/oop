#include <iostream>
#include <iterator>
#include "primes.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"primes"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	int upperBound;
	try
	{
		size_t convertionEndPos;
		upperBound = std::stoi(argv[1], &convertionEndPos);
		if (argv[1][convertionEndPos]) throw std::exception();
	}
	catch (std::exception e)
	{
		cerr << "Upper bound is too large or is not a valid integer.\n";
		return 1;
	}

	const auto && primes = GeneratePrimeNumbersSet(upperBound);
	std::copy(primes.begin(), primes.end(), std::ostream_iterator<int>(std::cout, "\n"));
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName) programName = "primes";
	cerr << "Usage: " << programName << " <upper bound>\n";
}
