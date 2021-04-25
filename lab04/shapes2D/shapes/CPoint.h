#pragma once
#include <cmath>
#include <iostream>

class CPoint
{
public:
	double x, y;

	double Distance(CPoint const& other)const
	{
		const double xDist = x - other.x, yDist = y - other.y;
		return sqrt(xDist * xDist + yDist * yDist);
	}
};

inline std::istream & operator >>(std::istream & input, CPoint & point)
{
	return input >> point.x >> point.y;
}

inline std::ostream & operator <<(std::ostream & output, CPoint const& point)
{
	return output << '(' << point.x << "; " << point.y << ')';
}
