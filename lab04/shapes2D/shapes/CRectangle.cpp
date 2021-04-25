#include <sstream>
#include "CRectangle.h"

constexpr static char RECTANGLE_FORMAT[] = "rectangle format: <left> <top> <width> <height> <outline color> <fill color>";

std::string CRectangle::ToString()const
{
	std::ostringstream desc;
	desc << "rectangle with top left point at " << m_topLeft;
	desc << ", width " << m_width << ", height " << m_height;
	return desc.str();
}

CRectangle *CRectangle::ReadFromStream(std::istream & input)
{
	input >> m_topLeft >> m_width >> m_height;
	input >> std::hex >> m_outlineColor >> m_fillColor;

	if (!input)
	{
		throw std::invalid_argument(RECTANGLE_FORMAT);
	}
	return this;
}
