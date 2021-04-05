#include "vector-proc.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"variant3"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	DoubleVector numbers;
	if (!ReadVector(std::cin, numbers))
	{
		PrintUsage(argv[0]);
		return 1;
	}

	ProcessVector(numbers);
	WriteVector(std::cout, numbers);
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName)
	{
		programName = "variant3";
	}
	cerr << "Usage: " << programName << '\n';
	cerr << "Multiply every multiple of 3 by the average of multiples of 2.\n";
}
