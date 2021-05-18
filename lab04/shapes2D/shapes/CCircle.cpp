#include <iomanip>
#include "CCircle.h"

std::string CCircle::ToString()const
{
	std::ostringstream desc;
	desc << "circle with the center at " << m_center
	     << ", radius " << m_radius
	     << std::hex << std::setfill('0')
	     << ", outline color #" << std::setw(6) << m_outlineColor
	     << ", fill color #" << std::setw(6) << m_fillColor;
	return desc.str();
}
