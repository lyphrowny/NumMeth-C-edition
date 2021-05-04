#include <stdlib.h>

#include "invit.h"

void LUDooDec(float** L, float** U, const float** A, const size_t* order) {
    for (size_t i = 0; i < *order; i++) {
        for (size_t j = 0; j < *order; j++) {
            if (i <= j) {
                U[i][j] = A[i][j];
                for (size_t k = 0; k < i; k++)
                    U[i][j] -= L[i][k] * U[k][j];
                L[i][j] = (i == j ? 1. : 0.);
            } else {
                L[i][j] = A[i][j];
                for (size_t k = 0; k < j; k++)
                    L[i][j] -= L[i][k] * U[k][j];
                L[i][j] /= U[j][j];
                U[i][j] = 0.;
            }
        }
    }
}