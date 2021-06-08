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
