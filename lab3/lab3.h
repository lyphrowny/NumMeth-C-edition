#pragma once

#include <stdlib.h>

void freeMat(const size_t* rows, double** mat);

double** readMatrix(size_t* rows, size_t* cols, const char* filename);

void printMatrix(const size_t* rows, const size_t* cols, double** mat);

void appendSolution(const size_t* rows, const double* solution, const char* filename);