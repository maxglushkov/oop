#include <iomanip>
#include "CRectangle.h"

std::string CRectangle::ToString()const
{
	std::ostringstream desc;
	desc << "rectangle with top left point at " << m_topLeft
	     << ", width " << m_width
	     << ", height " << m_height
	     << ", " << ISolidShape::ToString();
	return desc.str();
}
