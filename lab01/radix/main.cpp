#include <iostream>
#include "format-int.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"radix"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc != 4)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	bool wasError;
	const int sourceNotation = StringToInt(argv[1], 10, wasError);
	if (!IsValidRadix(sourceNotation))
	{
		PrintRadixConstraints();
		return 1;
	}

	const int destinationNotation = StringToInt(argv[2], 10, wasError);
	if (!IsValidRadix(destinationNotation))
	{
		PrintRadixConstraints();
		return 1;
	}

	const int intValue = StringToInt(argv[3], sourceNotation, wasError);
	if (wasError)
	{
		cerr << "The number is too big or has invalid format.\n";
		return 1;
	}

	const std::string & strValue = IntToString(intValue, destinationNotation, wasError);
	std::cout << strValue << '\n';
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName) programName = "radix";
	cerr << "Usage: " << programName << " <source notation> <destination notation> <value>\n";
}
