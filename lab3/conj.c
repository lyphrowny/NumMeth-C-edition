#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>

#include "conj.h"

size_t K = 0;

void mat_vecMul(double* dest, const double** mat, const double* vec, const size_t* order) {
    for (size_t i = 0; i < *order; i++) {
        dest[i] = 0;
        for (size_t j = 0; j < *order; j++)
            dest[i] += mat[i][j] * vec[j];
    }
}

double norm2(const double* vec, const size_t* order) {
    double sum = 0;
    for (size_t i = 0; i < *order; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
}

double dot(const double* vec1, const double* vec2, const size_t* order) {
    double sum = 0;
    for (size_t i = 0; i < *order; i++)
        sum += vec1[i] * vec2[i];
    return sum;
}

void linComb(double* dest, const double a, double* vec1, const double b, double* vec2, const size_t* order) {
    for (size_t i = 0; i < *order; i++)
        dest[i] = a * vec1[i] + b * vec2[i];
}

void CGM(double* dest, double** mat, double* b, const double* eps, const size_t* order) {
    size_t vec_size = sizeof(double) * *order;
    memset(dest, 0, vec_size);
    double* r = malloc(vec_size), * r_ = malloc(vec_size), * p = malloc(vec_size);
    double* q = malloc(vec_size);
    mat_vecMul(q, mat, dest, order);
    linComb(r, 1.0, b, -1.0, q, order);
    memcpy(p, r, vec_size);

    K = 0;
    double alpha, beta, norm;
    printf("\n\neps: %20.17lf\n", *eps);
    while (norm2(r, order) > *eps) {
        mat_vecMul(q, mat, p, order);
        alpha = dot(r, r, order) / dot(p, q, order);
        linComb(dest, 1.0, dest, alpha, p, order);
        memcpy(r_, r, vec_size);
        linComb(r, 1.0, r, -alpha, q, order);
        norm = norm2(r, order);
        printf("it: %zu, prec: %20.17lf\n", K, norm);
        if (norm <= *eps)
            break;
        beta = dot(r, r, order) / dot(r_, r_, order);
        linComb(p, 1.0, r, beta, p, order);
        K++;
    }
    free(p);
    free(q);
    free(r);
    free(r_);
}

size_t getIters() {
    return K;
}