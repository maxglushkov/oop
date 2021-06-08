#include <iomanip>
#include "CLineSegment.h"

std::string CLineSegment::ToString()const
{
	std::ostringstream desc;
	desc << "line segment with the beginning at " << m_start
	     << ", the end at " << m_end
	     << ", " << IShape::ToString();
	return desc.str();
}
