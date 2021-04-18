#include <iostream>
#include "car-controller-cli.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"car"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	Car car;
	const CarControllerCli controller(car, std::cin, std::cout, cerr);

	std::vector<std::string> arguments;
	CarControllerCli::Command command;
	while ((command = controller.PromptCommand(arguments)) != CarControllerCli::Command::Quit)
	{
		const CarControllerCli::Error error = controller.ExecCommand(command, arguments);
		if (error != CarControllerCli::Error::Success)
		{
			controller.PrintError(error);
		}
	}

	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName)
	{
		programName = "car";
	}
	cerr << "Usage: " << programName << '\n';
	cerr << "Lets the user drive a real virtual car.\n";
}
