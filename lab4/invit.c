#include <stdlib.h>

#include "invit.h"

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