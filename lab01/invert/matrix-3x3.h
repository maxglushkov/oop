#pragma once
#include <iostream>

class Matrix3x3
{
public:
	bool Read(std::istream & input);

	bool Write(std::ostream & output)const;

	Matrix3x3 CalculateInverseMatrix()const;

protected:
	constexpr static size_t SIDE = 3;

	Matrix3x3 CalculateTransposedCofactorsMatrix()const;

	double CalculateDeterminant(Matrix3x3 const& transposedCofactors)const;

private:
	double m_data[SIDE][SIDE];
};
