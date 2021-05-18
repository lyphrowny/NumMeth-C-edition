#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include "invit.h"

int K;

void LUDooDec(double** LU, const double** A, const size_t* order) {
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

void solveLU(double* res, const double** LU, const double* b, const size_t* order) {
    double* y = calloc(*order, sizeof(double));
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

double dot(const double* vec1, const double* vec2, const size_t* order) {
    double sum = 0;
    for (size_t i = 0; i < *order; i++)
        sum += vec1[i] * vec2[i];
    return sum;
}

void mat_vecMul(double* dest, const double** mat, const double* vec, const size_t* order) {
    for (size_t i = 0; i < *order; i++) {
        dest[i] = 0;
        for (size_t j = 0; j < *order; j++)
            dest[i] += mat[i][j] * vec[j];
    }
}

void vec_sc(double* dest, double* vec, double sc, const char op, const size_t* order) {
    for (size_t i = 0; i < *order; i++) {
        if (op == '/') dest[i] = vec[i] / sc;
        else if (op == '*') dest[i] = vec[i] * sc;
        else if (op == '+') dest[i] = vec[i] + sc;
        else dest[i] = vec[i] - sc;
    }
}

void linComb(double* dest, const double a, double* vec1, const double b, double* vec2, const size_t* order) {
    for (size_t i = 0; i < *order; i++)
        dest[i] = a * vec1[i] + b * vec2[i];
}

double infNorm(const double* vec, const size_t* order) {
    double sum = 0;
    for (size_t i = 0; i < *order; i++)
        if (sum < fabs(vec[i]))
            sum = vec[i];
    return sum;
}

double norm2(const double* vec, const size_t* order) {
    double sum = 0;
    for (size_t i = 0; i < *order; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
}

void
SPInvIt(double* dest, const double** A, const double** LU, double* vec, const double* tol, double* eig, const size_t* order) {
    double* temp = malloc(sizeof(double) * *order);
    double norm = infNorm(vec, order);
    vec_sc(dest, vec, norm, '/', order);
    K = 0;

    do {
        solveLU(vec, LU, dest, order);
        norm = infNorm(vec, order);
        vec_sc(dest, vec, norm, '/', order);
        K++;
        mat_vecMul(temp, A, dest, order);
        linComb(temp, 1.0, temp, -1./norm, dest, order);
    } while (norm2(temp, order) / norm2(dest, order) > *tol);
    *eig = 1 / norm;

    free(temp);
}

int getIters() {
    return K;
}