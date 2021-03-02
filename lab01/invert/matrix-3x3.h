#pragma once
#include <iostream>

constexpr size_t MATRIX_SIDE = 3;

template<typename T = double>
class Matrix3x3
{
public:
	friend std::istream & operator >>(std::istream & input, Matrix3x3 & matrix)
	{
		size_t x = 0, y = 0;
		while (y < MATRIX_SIDE)
		{
			input >> matrix.m_data[y][x];
			if (!input) break;

			if (++x == MATRIX_SIDE)
			{
				x = 0;
				++y;
			}
		}
		return input;
	}

	friend std::ostream & operator <<(std::ostream & output, Matrix3x3 const& matrix)
	{
		size_t x = 0, y = 0;
		while (y < MATRIX_SIDE)
		{
			output << matrix.m_data[y][x];
			if (!output) break;

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
			if (!output) break;
		}
		return output;
	}

	Matrix3x3 Invert() const
	{
		Matrix3x3 inverted;

		const T (& src)[MATRIX_SIDE][MATRIX_SIDE] = m_data;
		T (& dst)[MATRIX_SIDE][MATRIX_SIDE] = inverted.m_data;
		dst[0][0] = src[1][1] * src[2][2] - src[1][2] * src[2][1];
		dst[0][1] = src[0][2] * src[2][1] - src[0][1] * src[2][2];
		dst[0][2] = src[0][1] * src[1][2] - src[0][2] * src[1][1];
		dst[1][0] = src[1][2] * src[2][0] - src[1][0] * src[2][2];
		dst[1][1] = src[0][0] * src[2][2] - src[0][2] * src[2][0];
		dst[1][2] = src[0][2] * src[1][0] - src[0][0] * src[1][2];
		dst[2][0] = src[1][0] * src[2][1] - src[1][1] * src[2][0];
		dst[2][1] = src[0][1] * src[2][0] - src[0][0] * src[2][1];
		dst[2][2] = src[0][0] * src[1][1] - src[0][1] * src[1][0];

		const T det = src[0][0] * dst[0][0] + src[0][1] * dst[1][0] + src[0][2] * dst[2][0];
		if (!det) throw std::invalid_argument("singular matrix");

		for (size_t y = 0; y < MATRIX_SIDE; ++y)
		{
			for (size_t x = 0; x < MATRIX_SIDE; ++x)
			{
				dst[y][x] /= det;
			}
		}
		return inverted;
	}
private:
	T m_data[MATRIX_SIDE][MATRIX_SIDE];
};
