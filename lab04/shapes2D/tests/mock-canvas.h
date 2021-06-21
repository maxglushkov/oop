#pragma once
#include "fakeit.hpp"
#include "../shapes/CPoint.h"

inline bool operator ==(CPoint const& lhs, CPoint const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
