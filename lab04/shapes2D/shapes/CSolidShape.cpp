#include <iomanip>
#include "CSolidShape.h"

std::string CSolidShape::ToString()const
{
	std::ostringstream desc;
	desc << CShape::ToString()
	     << std::hex << std::setfill('0')
	     << ", fill color #" << std::setw(6) << GetFillColor();
	return desc.str();
}
