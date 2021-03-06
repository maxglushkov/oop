#include <iomanip>
#include "CShape.h"

std::string CShape::ToString()const
{
	std::ostringstream desc;
	desc << "area " << GetArea()
	     << ", perimeter " << GetPerimeter()
	     << std::hex << std::setfill('0')
	     << ", outline color #" << std::setw(6) << GetOutlineColor();
	return desc.str();
}
