#pragma once

#include <stdlib.h>

void freeMat(const size_t* rows, float** mat);

float** readMatrix(size_t* rows, size_t* cols, const char* filename);

void printMatrix(const size_t* rows, const size_t* cols, float** mat);

void appendSolution(const size_t* rows, const float* solution, const char* filename);