#pragma once

#include <stdlib.h>

void freeMat(const size_t* rows, double** mat);

double** allocateMat(const size_t* rows, const size_t* cols);

void freeFilenames(char** filenames, size_t capacity);

char** readDir(const char* dir_name, size_t* capacity);

double** readMatrix(size_t* rows, size_t* cols, const char* filename);

void printMat(const double** mat, const size_t* rows, const size_t* cols);

void printVec(const double* vec, const size_t* rows, const char* entrance, const char* exit);

void appendSolution(const size_t* rows, const double* solution, const char* filename);