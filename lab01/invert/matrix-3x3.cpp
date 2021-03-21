#include <sstream>
#include "matrix-3x3.h"

constexpr char ERROR_SINGULAR_MATRIX[] = "singular matrix";

bool Matrix3x3::Read(std::istream & input)
{
	std::string row;
	for (size_t y = 0; y < SIDE; ++y)
	{
		if (!std::getline(input, row))
		{
			return false;
		}

		std::istringstream inputRow(row);
		for (size_t x = 0; x < SIDE; ++x)
		{
			inputRow >> m_data[y][x];
			if (!inputRow)
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix3x3::Write(std::ostream & output)const
{
	size_t x = 0, y = 0;
	while (y < SIDE)
	{
		output << m_data[y][x];
		if (!output)
		{
			return false;
		}

		if (++x == SIDE)
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

Matrix3x3 Matrix3x3::CalculateInverseMatrix()const
{
	Matrix3x3 transposedCofactors = CalculateTransposedCofactorsMatrix();
	const double det = CalculateDeterminant(transposedCofactors);
	if (!det)
	{
		throw std::invalid_argument(ERROR_SINGULAR_MATRIX);
	}

	for (size_t y = 0; y < SIDE; ++y)
	{
		for (size_t x = 0; x < SIDE; ++x)
		{
			transposedCofactors.m_data[y][x] /= det;
		}
	}
	return transposedCofactors;
}

Matrix3x3 Matrix3x3::CalculateTransposedCofactorsMatrix()const
{
	Matrix3x3 transposedCofactors;

	auto const& src = m_data;
	auto & dst = transposedCofactors.m_data;
	dst[0][0] = src[1][1] * src[2][2] - src[1][2] * src[2][1];
	dst[0][1] = src[0][2] * src[2][1] - src[0][1] * src[2][2];
	dst[0][2] = src[0][1] * src[1][2] - src[0][2] * src[1][1];
	dst[1][0] = src[1][2] * src[2][0] - src[1][0] * src[2][2];
	dst[1][1] = src[0][0] * src[2][2] - src[0][2] * src[2][0];
	dst[1][2] = src[0][2] * src[1][0] - src[0][0] * src[1][2];
	dst[2][0] = src[1][0] * src[2][1] - src[1][1] * src[2][0];
	dst[2][1] = src[0][1] * src[2][0] - src[0][0] * src[2][1];
	dst[2][2] = src[0][0] * src[1][1] - src[0][1] * src[1][0];

	return transposedCofactors;
}

double Matrix3x3::CalculateDeterminant(Matrix3x3 const& transposedCofactors)const
{
	auto const& minorsT = transposedCofactors.m_data;
	return m_data[0][0] * minorsT[0][0] + m_data[0][1] * minorsT[1][0] + m_data[0][2] * minorsT[2][0];
}
