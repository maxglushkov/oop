#pragma once
#include <vector>
#include "../shapes/CPoint.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor) = 0;

	virtual void FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor) = 0;

	virtual void DrawCircle(CPoint const& center, double radius, uint32_t lineColor) = 0;

	virtual void FillCircle(CPoint const& center, double radius, uint32_t fillColor) = 0;
};
