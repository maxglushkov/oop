#include <fstream>
#include "matrix-3x3.h"
using std::cerr, std::cout;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"invert"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	const char *const matrixFile = argv[1];
	std::ifstream input(matrixFile);
	if (!input)
	{
		cerr << "Cannot open file \"" << matrixFile << "\" for input.\n";
		return 1;
	}

	Matrix3x3 matrix;
	if (!matrix.Read(input))
	{
		cerr << "Cannot load matrix from \"" << matrixFile << "\": input-output or format error.\n";
		return 1;
	}

	try
	{
		cout.setf(std::ios::fixed);
		cout.precision(3);
		matrix.Invert().Write(cout);
		return 0;
	}
	catch (std::invalid_argument e)
	{
		cerr << "Failed to invert matrix: " << e.what() << '\n';
	}
	return 1;
}

void PrintUsage(const char *programName)
{
	if (!programName) programName = "invert";
	cerr << "Usage: " << programName << " <matrix file1>\n";
}
