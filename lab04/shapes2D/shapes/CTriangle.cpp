#include <iomanip>
#include "CTriangle.h"

std::string CTriangle::ToString()const
{
	std::ostringstream desc;
	desc << "triangle with vertices at "
	     << m_vertices[0] << ", " << m_vertices[1] << ", " << m_vertices[2]
	     << std::hex << std::setfill('0')
	     << ", outline color #" << std::setw(6) << m_outlineColor
	     << ", fill color #" << std::setw(6) << m_fillColor;
	return desc.str();
}
