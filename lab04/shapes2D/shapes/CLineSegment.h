#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment: public IShape
{
public:
	CLineSegment(CPoint const& start, CPoint const& end, uint32_t color)
		:m_start(start)
		,m_end(end)
		,m_color(color)
	{
	}

	double GetArea()const
	{
		return 0;
	}

	double GetPerimeter()const
	{
		return m_start.Distance(m_end);
	}

	std::string ToString()const;

	uint32_t GetOutlineColor()const
	{
		return m_color;
	}

	CPoint GetStartPoint()const
	{
		return m_start;
	}

	CPoint GetEndPoint()const
	{
		return m_end;
	}

private:
	CPoint m_start, m_end;
	uint32_t m_color;
};
