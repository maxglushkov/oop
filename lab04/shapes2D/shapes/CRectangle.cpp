#include <iomanip>
#include "CRectangle.h"

std::string CRectangle::ToString()const
{
	std::ostringstream desc;
	desc << "rectangle with top left point at " << m_topLeft
	     << ", width " << m_width
	     << ", height " << m_height
	     << std::hex << std::setfill('0')
	     << ", outline color #" << std::setw(6) << m_outlineColor
	     << ", fill color #" << std::setw(6) << m_fillColor;
	return desc.str();
}
