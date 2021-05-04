#pragma once

void LUDooDec(float** LU, const float** A, const size_t* order);

void solveLU(float* res, const float** LU, const float* b, size_t* order);