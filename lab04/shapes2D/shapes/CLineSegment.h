#pragma once
#include "CPoint.h"
#include "CShape.h"
#include "../canvas/ICanvasDrawable.h"

class CLineSegment: public CShape, public ICanvasDrawable
{
public:
	CLineSegment(CPoint const& start, CPoint const& end, uint32_t color)
		:m_start(start)
		,m_end(end)
		,m_color(color)
	{
	}

	double GetArea()const override
	{
		return 0;
	}

	double GetPerimeter()const override
	{
		return m_start.Distance(m_end);
	}

	std::string ToString()const override;

	uint32_t GetOutlineColor()const override
	{
		return m_color;
	}

	void Draw(ICanvas & canvas)const override;

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
