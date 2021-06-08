#include <iomanip>
#include "ISolidShape.h"

std::string ISolidShape::ToString()const
{
	std::ostringstream desc;
	desc << IShape::ToString()
	     << std::hex << std::setfill('0')
	     << ", fill color #" << std::setw(6) << GetFillColor();
	return desc.str();
}
