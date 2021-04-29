#pragma once

float** readMatrix(size_t *rows, size_t *cols, const char *filename);
void printMatrix(const size_t *rows, const size_t* cols, float** mat);
void rotate(const size_t *rows, const size_t* cols, float** mat); // in-place
void freeMatrix(const size_t* rows, float** mat);
float* reverse(const size_t* rows, const size_t* cols, float** mat);
void appendSolution(const size_t* rows, const float* solution, const char* filename);
float norm(const size_t* rows, float* vec);