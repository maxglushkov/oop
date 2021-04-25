#include <sstream>
#include "CLineSegment.h"

constexpr static char LINE_SEGMENT_FORMAT[] = "segment format: <start x> <start y> <end x> <end y> <color>";

std::string CLineSegment::ToString()const
{
	std::ostringstream desc;
	desc << "line segment with the beginning at " << m_start << " and the end at " << m_end;
	return desc.str();
}

CLineSegment *CLineSegment::ReadFromStream(std::istream & input)
{
	input >> m_start >> m_end;
	input >> std::hex >> m_color;

	if (!input)
	{
		throw std::invalid_argument(LINE_SEGMENT_FORMAT);
	}
	return this;
}
