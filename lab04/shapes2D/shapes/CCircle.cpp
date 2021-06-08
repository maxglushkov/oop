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
