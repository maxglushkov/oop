#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle: public ISolidShape
{
public:
	CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3,
	          uint32_t outlineColor, uint32_t fillColor)
		:m_vertices{vertex1, vertex2, vertex3}
		,m_outlineColor(outlineColor)
		,m_fillColor(fillColor)
	{
	}

	double GetArea()const
	{
		const double a = m_vertices[0].Distance(m_vertices[1]);
		const double b = m_vertices[0].Distance(m_vertices[2]);
		const double c = m_vertices[1].Distance(m_vertices[2]);
		const double p = (a + b + c) / 2.0;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

	double GetPerimeter()const
	{
		return m_vertices[0].Distance(m_vertices[1])
		     + m_vertices[0].Distance(m_vertices[2])
		     + m_vertices[1].Distance(m_vertices[2]);
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

	CPoint GetVertex1()const
	{
		return m_vertices[0];
	}

	CPoint GetVertex2()const
	{
		return m_vertices[1];
	}

	CPoint GetVertex3()const
	{
		return m_vertices[2];
	}

private:
	CPoint m_vertices[3];
	uint32_t m_outlineColor, m_fillColor;
};
