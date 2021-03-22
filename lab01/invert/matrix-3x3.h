#pragma once
#include <iostream>

constexpr size_t MATRIX_SIDE = 3;
typedef double Matrix3x3[MATRIX_SIDE][MATRIX_SIDE];

bool ReadMatrix(std::istream & input, Matrix3x3 & matrix);

bool WriteMatrix(std::ostream & output, Matrix3x3 const& matrix);

bool InvertMatrix(Matrix3x3 const& original, Matrix3x3 & inverted);
