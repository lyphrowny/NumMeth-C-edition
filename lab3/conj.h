#pragma once

void mat_vecMul(float* dest, const float** mat, const float* vec, const size_t* order);
double norm2(const float* vec, const size_t* order);
double dot(const float* vec1, const float* vec2, const size_t* order);
void linComb(float* dest, float a, float* vec1, float b, float* vec2, const size_t* order);
void CGM(float* dest, float** mat, float* b, const float* eps, const size_t* order);
size_t getIters();