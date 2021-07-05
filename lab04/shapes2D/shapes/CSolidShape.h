#pragma once
#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape: public ISolidShape, private CShape
{
public:
	std::string ToString()const override;
};
