#include <sstream>
#include "matrix-3x3.h"

bool ReadMatrix(std::istream & input, Matrix3x3 & matrix)
{
	std::string row;
	for (size_t y = 0; y < MATRIX_SIDE; ++y)
	{
		if (!std::getline(input, row))
		{
			return false;
		}

		std::istringstream inputRow(row);
		for (size_t x = 0; x < MATRIX_SIDE; ++x)
		{
			inputRow >> matrix[y][x];
			if (!inputRow)
			{
				return false;
			}
		}
	}
	return true;
}

bool WriteMatrix(std::ostream & output, Matrix3x3 const& matrix)
{
	size_t x = 0, y = 0;
	while (y < MATRIX_SIDE)
	{
		output << matrix[y][x];
		if (!output)
		{
			return false;
		}

		if (++x == MATRIX_SIDE)
		{
			x = 0;
			++y;
			output << '\n';
		}
		else
		{
			output << '\t';
		}
		if (!output)
		{
			return false;
		}
	}
	return true;
}

bool InvertMatrix(Matrix3x3 const& original, Matrix3x3 & inverted)
{
	inverted[0][0] = original[1][1] * original[2][2] - original[1][2] * original[2][1];
	inverted[1][0] = original[1][2] * original[2][0] - original[1][0] * original[2][2];
	inverted[2][0] = original[1][0] * original[2][1] - original[1][1] * original[2][0];

	const double det = original[0][0] * inverted[0][0] + original[0][1] * inverted[1][0] + original[0][2] * inverted[2][0];
	if (!det)
	{
		return false;
	}

	inverted[0][1] = original[0][2] * original[2][1] - original[0][1] * original[2][2];
	inverted[0][2] = original[0][1] * original[1][2] - original[0][2] * original[1][1];
	inverted[1][1] = original[0][0] * original[2][2] - original[0][2] * original[2][0];
	inverted[1][2] = original[0][2] * original[1][0] - original[0][0] * original[1][2];
	inverted[2][1] = original[0][1] * original[2][0] - original[0][0] * original[2][1];
	inverted[2][2] = original[0][0] * original[1][1] - original[0][1] * original[1][0];

	for (size_t y = 0; y < MATRIX_SIDE; ++y)
	{
		for (size_t x = 0; x < MATRIX_SIDE; ++x)
		{
			inverted[y][x] /= det;
		}
	}
	return true;
}
