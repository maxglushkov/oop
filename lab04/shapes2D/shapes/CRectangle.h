#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include "../canvas/ICanvasDrawable.h"

class CRectangle: public ISolidShape, public ICanvasDrawable
{
public:
	CRectangle(CPoint const& topLeft, double width, double height, uint32_t outlineColor, uint32_t fillColor)
		:m_topLeft(topLeft)
		,m_width(width)
		,m_height(height)
		,m_outlineColor(outlineColor)
		,m_fillColor(fillColor)
	{
		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("width and height cannot be less then zero");
		}
	}

	double GetArea()const override
	{
		return m_width * m_height;
	}

	double GetPerimeter()const override
	{
		return 2 * (m_width + m_height);
	}

	std::string ToString()const override;

	uint32_t GetOutlineColor()const override
	{
		return m_outlineColor;
	}

	uint32_t GetFillColor()const override
	{
		return m_fillColor;
	}

	void Draw(ICanvas & canvas)const override;

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

private:
	CPoint m_topLeft;
	double m_width, m_height;
	uint32_t m_outlineColor, m_fillColor;
};
