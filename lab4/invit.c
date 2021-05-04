#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include "invit.h"

int K;

void LUDooDec(float** LU, const float** A, const size_t* order) {
    for (size_t i = 0; i < *order; i++) {
        for (size_t j = 0; j < *order; j++) {
            LU[i][j] = A[i][j];
            if (i <= j)
                for (size_t k = 0; k < i; k++)
                    LU[i][j] -= LU[i][k] * LU[k][j];
            else {
                for (size_t k = 0; k < j; k++)
                    LU[i][j] -= LU[i][k] * LU[k][j];
                LU[i][j] /= LU[j][j];
            }
        }
    }
}

void solveLU(float* res, const float** LU, const float* b, size_t* order) {
    float* y = calloc(*order, sizeof(float));
    for (size_t i = 0; i < *order; i++) {
        y[i] = b[i];
        for (size_t j = 0; j < i; j++)
            y[i] -= LU[i][j] * y[j];
    }
    for (size_t i = *order - 1; i < *order; i--) {
        res[i] = y[i];
        for (size_t j = i + 1; j < *order; j++)
            res[i] -= LU[i][j] * res[j];
        res[i] /= LU[i][i];
    }
    free(y);
}

float dot(const float* vec1, const float* vec2, const size_t* order) {
    float sum = 0;
    for (size_t i = 0; i < *order; i++)
        sum += vec1[i] * vec2[i];
    return sum;
}

void vec_sc(float* dest, float* vec, float sc, const char op, const size_t* order) {
    for (size_t i = 0; i < *order; i++) {
        if (op == '/') dest[i] = vec[i] / sc;
        else if (op == '*') dest[i] = vec[i] * sc;
        else if (op == '+') dest[i] = vec[i] + sc;
        else dest[i] = vec[i] - sc;
    }
}

float infNorm(const float* vec, const size_t* order) {
    float sum = 0;
    for (size_t i = 0; i < *order; i++)
        if (sum < fabs(vec[i]))
            sum = vec[i];
    return sum;
}

void
SPInvIt(float* dest, const float** A, const float** LU, float* vec, const float* tol, float* eig, const size_t* order) {
    float eig_, norm = infNorm(vec, order);
    vec_sc(dest, vec, norm, '/', order);
    K = 0;

    do {
        solveLU(vec, LU, dest, order);
        eig_ = *eig, norm = infNorm(vec, order), *eig = 1 / norm;
        vec_sc(dest, vec, norm, '/', order);
        K++;
    } while (fabs(*eig - eig_) > *tol);
}

int getIters() {
    return K;
}