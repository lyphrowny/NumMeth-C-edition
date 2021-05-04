#pragma once

void LUDooDec(float** LU, const float** A, const size_t* order);

void solveLU(float* res, const float** LU, const float* b, size_t* order);

void
SPInvIt(float* dest, const float** A, const float** LU, float* vec, const float* tol, float* eig, const size_t* order);

int getIters();