#pragma once
#include "IShape.h"

class CShape: public virtual IShape
{
public:
	std::string ToString()const override;
};
