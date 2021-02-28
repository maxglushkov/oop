#pragma once
#include <iostream>

constexpr size_t MATRIX_SIDE = 3;

template<typename T = double>
class Matrix3x3
{
public:
	friend std::istream & operator >>(std::istream & input, Matrix3x3 & matrix)
	{
		for (size_t y = 0; y < MATRIX_SIDE; ++y)
		{
			for (size_t x = 0; x < MATRIX_SIDE; ++x)
			{
				input >> matrix.m_data[y][x];
				if (!input) return input;
			}
		}
		return input;
	}

	friend std::ostream & operator <<(std::ostream & output, Matrix3x3 const& matrix)
	{
		output.precision(3);
		for (size_t y = 0; y < MATRIX_SIDE; ++y)
		{
			for (size_t x = 0; x < MATRIX_SIDE; ++x)
			{
				output << matrix.m_data[y][x] << '\t';
				if (!output) return output;
			}
			output << '\n';
			if (!output) return output;
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
		if (!det) throw std::invalid_argument("Singular matrix");

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
