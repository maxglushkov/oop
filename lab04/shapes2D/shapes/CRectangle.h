#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle: public ISolidShape
{
public:
	double GetArea()const
	{
		return m_width * m_height;
	}

	double GetPerimeter()const
	{
		return 2 * (m_width + m_height);
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

	CPoint GetLeftTop()const
	{
		return m_topLeft;
	}

	CPoint GetRightBottom()const
	{
		return {
			m_topLeft.x + m_width,
			m_topLeft.y + m_height
		};
	}

	double GetWidth()const
	{
		return m_width;
	}

	double GetHeight()const
	{
		return m_height;
	}

	CRectangle *ReadFromStream(std::istream & input);

private:
	CPoint m_topLeft;
	double m_width, m_height;
	uint32_t m_outlineColor, m_fillColor;
};