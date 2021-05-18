#pragma once

void LUDooDec(double** LU, const double** A, const size_t* order);

void solveLU(double* res, const double** LU, const double* b, const size_t* order);

void
SPInvIt(double* dest, const double** A, const double** LU, double* vec, const double* tol, double* eig, const size_t* order);

int getIters();