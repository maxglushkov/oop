#include <iomanip>
#include "CCircle.h"

std::string CCircle::ToString()const
{
	std::ostringstream desc;
	desc << "circle with the center at " << m_center
	     << ", radius " << m_radius
	     << ", " << ISolidShape::ToString();
	return desc.str();
}

void CCircle::Draw(ICanvas & canvas)const
{
	canvas.FillCircle(m_center, m_radius, m_fillColor);
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}
