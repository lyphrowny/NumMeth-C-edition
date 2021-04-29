#pragma once

#include <stdlib.h>

float dotProduct(const size_t* cols, const float* vec1, const float* vec2);

float** sc_matMul(const float* scal, const size_t* rows, const size_t* cols, const float** mat);

// [a, b] * [b, c] -> [a, c]
float** mat_matMul(const size_t* rows, const size_t* _cols, const size_t* cols, const float** mat1, const float** mat2);

float** mat_matSub(const size_t* rows, const size_t* cols, const float** mat1, const float** mat2);

void freeMat(const size_t* rows, float** mat);

float** readMatrix(size_t* rows, size_t* cols, const char* filename);

void printMatrix(const size_t* rows, const size_t* cols, float** mat);

void appendSolution(const size_t* rows, const float* solution, const char* filename);