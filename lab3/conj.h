#pragma once

void mat_vecMul(double* dest, const double** mat, const double* vec, const size_t* order);
double norm2(const double* vec, const size_t* order);
double dot(const double* vec1, const double* vec2, const size_t* order);
void linComb(double* dest, double a, double* vec1, double b, double* vec2, const size_t* order);
void CGM(double* dest, double** mat, double* b, const double* eps, const size_t* order);
size_t getIters();