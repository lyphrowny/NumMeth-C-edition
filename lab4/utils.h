#pragma once

#include <stdlib.h>

void freeMat(const size_t* rows, float** mat);

void freeFilenames(char** filenames, size_t capacity);

char** readDir(const char* dir_name, size_t* capacity);

float** readMatrix(size_t* rows, size_t* cols, const char* filename);

void printMat(const float** mat, const size_t* rows, const size_t* cols);

void printVec(const float* vec, const size_t* rows, const char* entrance, const char* exit);

void appendSolution(const size_t* rows, const float* solution, const char* filename);