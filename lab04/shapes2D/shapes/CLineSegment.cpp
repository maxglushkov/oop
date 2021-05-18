#include <iomanip>
#include "CLineSegment.h"

std::string CLineSegment::ToString()const
{
	std::ostringstream desc;
	desc << "line segment with the beginning at " << m_start
	     << ", the end at " << m_end
	     << std::hex << std::setfill('0')
	     << ", color #" << std::setw(6) << m_color;
	return desc.str();
}
