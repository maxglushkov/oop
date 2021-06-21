#include <iomanip>
#include "CTriangle.h"

std::string CTriangle::ToString()const
{
	std::ostringstream desc;
	desc << "triangle with vertices at "
	     << m_vertices[0] << ", " << m_vertices[1] << ", " << m_vertices[2]
	     << ", " << ISolidShape::ToString();
	return desc.str();
}

void CTriangle::Draw(ICanvas & canvas)const
{
	canvas.FillPolygon(std::vector(m_vertices, m_vertices + 3), m_fillColor);
	canvas.DrawLine(m_vertices[0], m_vertices[1], m_outlineColor);
	canvas.DrawLine(m_vertices[1], m_vertices[2], m_outlineColor);
	canvas.DrawLine(m_vertices[2], m_vertices[0], m_outlineColor);
}
