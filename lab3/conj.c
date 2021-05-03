#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "conj.h"

size_t K = 0;

void mat_vecMul(float* dest, const float** mat, const float* vec, const size_t* order) {
    for (size_t i = 0; i < *order; i++) {
        dest[i] = 0;
        for (size_t j = 0; j < *order; j++)
            dest[i] += mat[i][j] * vec[j];
    }
}

double norm2(const float* vec, const size_t* order) {
    double sum = 0;
    for (size_t i = 0; i < *order; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
}

double dot(const float* vec1, const float* vec2, const size_t* order) {
    double sum = 0;
    for (size_t i = 0; i < *order; i++)
        sum += vec1[i] * vec2[i];
    return sum;
}

void linComb(float* dest, const float a, float* vec1, const float b, float* vec2, const size_t* order) {
    for (size_t i = 0; i < *order; i++)
        dest[i] = a * vec1[i] + b * vec2[i];
}

void CGM(float* dest, float** mat, float* b, const float* eps, const size_t* order) {
    size_t vec_size = sizeof(float) * *order;
    memset(dest, 0, vec_size);
    float* r = malloc(vec_size), *r_ = malloc(vec_size), * p = malloc(vec_size);
    float* q = malloc(vec_size);
    mat_vecMul(q, mat, dest, order);
    linComb(r, 1.0, b, -1.0, q, order);
    memcpy(p, r, vec_size);

    K = 0;
    float alpha, beta;

    while (norm2(r, order) > *eps && K++ < *order) {
        mat_vecMul(q, mat, p, order);
        alpha = dot(r, r, order) / dot(p, q, order);
        linComb(dest, 1.0, dest, alpha, p, order);
        memcpy(r_, r, vec_size);
        linComb(r, 1.0, r, -alpha, q, order);
        if (norm2(r, order) <= *eps)
            break;
        beta = dot(r, r, order) / dot(r_, r_, order);
        linComb(p, 1.0, r, beta, p, order);
    }
    free(p);
    free(q);
    free(r);
    free(r_);
}

size_t getIters() {
    return K;
}