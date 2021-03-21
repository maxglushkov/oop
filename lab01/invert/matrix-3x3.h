#pragma once
#include <iostream>

constexpr size_t MATRIX_SIDE = 3;
typedef double Matrix3x3[MATRIX_SIDE][MATRIX_SIDE];

bool ReadMatrix(std::istream & input, Matrix3x3 matrix);

bool WriteMatrix(std::ostream & output, const Matrix3x3 matrix);

bool InvertMatrix(const Matrix3x3 original, Matrix3x3 inverted);
