#pragma once

#include <stdlib.h>

float dotProduct(const size_t* rows, const float* vec1, const float* vec2);

float** sc_matMul(const float* scal, const size_t* rows, const size_t* cols, const float** mat);

float* sc_vecMul(const float* scal, const size_t* rows, const float* vec, float* res);

// [a, b] * [b, c] -> [a, c]
float** mat_matMul(const size_t* rows, const size_t* _cols, const size_t* cols, const float** mat1, const float** mat2);

// [n, m] x [m, 1] -> [n, 1]
float* mat_vecMul(const float* vec, const size_t* rows, const size_t* cols, const float** mat, float* res);

float** mat_matSub(const size_t* rows, const size_t* cols, const float** mat1, const float** mat2);

float* vec_vecSub(const size_t* rows, const float* vec1, const float* vec2, float* res);

float* vec_vecAdd(const size_t* rows, const float* vec1, const float* vec2, float* res);

void freeMat(const size_t* rows, float** mat);

float** readMatrix(size_t* rows, size_t* cols, const char* filename);

void printMatrix(const size_t* rows, const size_t* cols, float** mat);

void printVec(const char* entrance, const char* exit, const size_t* rows, const float* vec);

void appendSolution(const size_t* rows, const float* solution, const char* filename);

float norm2(const size_t* rows, const float* vec);

float* CGM(const float* precision, const size_t* rows, const size_t* cols, const float** mat, const float* b);