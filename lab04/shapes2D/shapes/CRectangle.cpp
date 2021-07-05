#include <iomanip>
#include "CRectangle.h"

std::string CRectangle::ToString()const
{
	std::ostringstream desc;
	desc << "rectangle with top left point at " << m_topLeft
	     << ", width " << m_width
	     << ", height " << m_height
	     << ", " << CSolidShape::ToString();
	return desc.str();
}

void CRectangle::Draw(ICanvas & canvas)const
{
	const double left = m_topLeft.x, right = m_topLeft.x + m_width;
	const double top = m_topLeft.y, bottom = m_topLeft.y + m_height;

	const std::vector<CPoint> points{
		m_topLeft,
		{right, top},
		{right, bottom},
		{left, bottom}
	};
	canvas.FillPolygon(points, m_fillColor);
	canvas.DrawLine(points[0], points[1], m_outlineColor);
	canvas.DrawLine(points[1], points[2], m_outlineColor);
	canvas.DrawLine(points[2], points[3], m_outlineColor);
	canvas.DrawLine(points[3], points[0], m_outlineColor);
}
