#pragma once
#include <iostream>
#include <vector>

typedef std::vector<double> Vector;

bool ReadVector(std::istream & input, Vector & vector);

void ProcessVector(Vector & vector);

bool WriteVector(std::ostream & output, Vector const& vector);
