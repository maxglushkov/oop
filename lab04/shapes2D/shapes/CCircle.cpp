#include <sstream>
#include "CCircle.h"

constexpr static char CIRCLE_FORMAT[] = "circle format: <center x> <center y> <radius> <outline color> <fill color>";

std::string CCircle::ToString()const
{
	std::ostringstream desc;
	desc << "circle with the center at " << m_center << " and radius " << m_radius;
	return desc.str();
}

CCircle *CCircle::ReadFromStream(std::istream & input)
{
	input >> m_center >> m_radius;
	input >> std::hex >> m_outlineColor >> m_fillColor;

	if (!input || m_radius < 0)
	{
		throw std::invalid_argument(CIRCLE_FORMAT);
	}
	return this;
}
