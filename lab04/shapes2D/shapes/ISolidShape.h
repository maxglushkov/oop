#pragma once
#include "IShape.h"

class ISolidShape: public IShape
{
public:
	std::string ToString()const override;

	virtual uint32_t GetFillColor()const = 0;
};
