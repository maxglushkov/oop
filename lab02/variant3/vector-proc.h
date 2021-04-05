#pragma once
#include <iostream>
#include <vector>

typedef std::vector<double> DoubleVector;

bool ReadVector(std::istream & input, DoubleVector & vector);

void ProcessVector(DoubleVector & vector);

bool WriteVector(std::ostream & output, DoubleVector const& vector);
