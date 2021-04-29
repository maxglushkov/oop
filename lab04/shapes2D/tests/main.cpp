#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "main.h"

void IgnoreInvalidShape(std::istream & input)
{
	input.clear();
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
