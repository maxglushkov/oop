#include <sstream>
#include "CTriangle.h"

constexpr static char TRIANGLE_FORMAT[] = "triangle format: <1 vertex x> <1 vertex y> <2 vertex x> <2 vertex y> <3 vertex x> <3 vertex y> <outline color> <fill color>";

std::string CTriangle::ToString()const
{
	std::ostringstream desc;
	desc << "triangle with vertices at ";
	desc << m_vertices[0] << ", " << m_vertices[1] << ", " << m_vertices[2];
	return desc.str();
}

CTriangle *CTriangle::ReadFromStream(std::istream & input)
{
	for (CPoint & vertex: m_vertices)
	{
		input >> vertex;
	}
	input >> std::hex >> m_outlineColor >> m_fillColor;

	if (!input)
	{
		throw std::invalid_argument(TRIANGLE_FORMAT);
	}
	return this;
}
