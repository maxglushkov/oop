#pragma once
#include <iostream>

class Matrix3x3
{
public:
	bool Read(std::istream & input);

	bool Write(std::ostream & output)const;

	Matrix3x3 Invert()const;

private:
	constexpr static size_t SIDE = 3;
	double m_data[SIDE][SIDE];
};
