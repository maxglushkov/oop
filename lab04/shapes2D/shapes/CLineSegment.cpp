#include <iomanip>
#include "CLineSegment.h"

std::string CLineSegment::ToString()const
{
	std::ostringstream desc;
	desc << "line segment with the beginning at " << m_start
	     << ", the end at " << m_end
	     << ", " << CShape::ToString();
	return desc.str();
}

void CLineSegment::Draw(ICanvas & canvas)const
{
	canvas.DrawLine(m_start, m_end, m_color);
}
