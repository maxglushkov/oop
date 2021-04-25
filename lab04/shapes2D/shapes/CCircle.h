#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle: public ISolidShape
{
public:
	double GetArea()const
	{
		return M_PI * m_radius * m_radius;
	}

	double GetPerimeter()const
	{
		return 2 * M_PI * m_radius;
	}

	std::string ToString()const;

	uint32_t GetOutlineColor()const
	{
		return m_outlineColor;
	}

	uint32_t GetFillColor()const
	{
		return m_fillColor;
	}

	CPoint GetCenter()const
	{
		return m_center;
	}

	double GetRadius()const
	{
		return m_radius;
	}

	CCircle *ReadFromStream(std::istream & input);

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor, m_fillColor;
};
