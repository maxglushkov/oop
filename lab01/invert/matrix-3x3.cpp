#include "matrix-3x3.h"

std::istream & Matrix3x3::Read(std::istream & input)
{
	size_t x = 0, y = 0;
	while (y < SIDE)
	{
		input >> m_data[y][x];
		if (!input) break;

		if (++x == SIDE)
		{
			x = 0;
			++y;
		}
	}
	return input;
}

std::ostream & Matrix3x3::Write(std::ostream & output)const
{
	size_t x = 0, y = 0;
	while (y < SIDE)
	{
		output << m_data[y][x];
		if (!output) break;

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
		if (!output) break;
	}
	return output;
}

Matrix3x3 Matrix3x3::Invert() const
{
	Matrix3x3 inverted;

	const auto & src = m_data;
	auto & dst = inverted.m_data;
	dst[0][0] = src[1][1] * src[2][2] - src[1][2] * src[2][1];
	dst[0][1] = src[0][2] * src[2][1] - src[0][1] * src[2][2];
	dst[0][2] = src[0][1] * src[1][2] - src[0][2] * src[1][1];
	dst[1][0] = src[1][2] * src[2][0] - src[1][0] * src[2][2];
	dst[1][1] = src[0][0] * src[2][2] - src[0][2] * src[2][0];
	dst[1][2] = src[0][2] * src[1][0] - src[0][0] * src[1][2];
	dst[2][0] = src[1][0] * src[2][1] - src[1][1] * src[2][0];
	dst[2][1] = src[0][1] * src[2][0] - src[0][0] * src[2][1];
	dst[2][2] = src[0][0] * src[1][1] - src[0][1] * src[1][0];

	const double det = src[0][0] * dst[0][0] + src[0][1] * dst[1][0] + src[0][2] * dst[2][0];
	if (!det) throw std::invalid_argument("singular matrix");

	for (size_t y = 0; y < SIDE; ++y)
	{
		for (size_t x = 0; x < SIDE; ++x)
		{
			dst[y][x] /= det;
		}
	}
	return inverted;
}
