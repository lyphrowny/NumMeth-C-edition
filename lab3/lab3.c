#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "lab3.h"

float dotProduct(const size_t* rows, const float* vec1, const float* vec2) {
    float res = 0;
    for (size_t i = 0; i < *rows; i++)
        res += vec1[i] * vec2[i];
    return res;
}

float** sc_matMul(const float* scal, const size_t* rows, const size_t* cols, const float** mat) {
    float** res;
    res = malloc(sizeof *res * *rows);
    if (res) {
        for (size_t i = 0; i < *rows; i++) {
            res[i] = malloc(sizeof *res[i] * *cols);
            for (size_t j = 0; j < *cols; j++)
                res[i][j] = *scal * mat[i][j];
        }
    }
    return res;
}

float* sc_vecMul(const float* scal, const size_t* rows, const float* vec, float* res) {
    if (res == NULL)
        res = malloc(sizeof(float) * *rows);
    if (res != NULL)
        for (size_t i = 0; i < *rows; i++)
            res[i] = vec[i] * *scal;
    return res;
}

// [a, b] * [b, c] -> [a, c]
float**
mat_matMul(const size_t* rows, const size_t* _cols, const size_t* cols, const float** mat1, const float** mat2) {
    float** res = NULL;
    if ((res = malloc(sizeof *res * *rows)) != NULL)
        for (size_t i = 0; i < *rows; i++)
            if ((res[i] = malloc(sizeof *res[i] * *cols)) != NULL)
                for (size_t k = 0; k < *cols; k++) {
                    res[i][k] = 0;
                    for (size_t j = 0; j < *_cols; j++)
                        res[i][k] += mat1[i][j] * mat2[j][k];
                }
    return res;
}

// [n, m] x [m, 1] -> [n, 1]
float* mat_vecMul(const float* vec, const size_t* rows, const size_t* cols, const float** mat, float* res) {
    if (res == NULL)
        res = malloc(sizeof(float) * *rows);
    if (res != NULL) {
        memset(res, 0, sizeof(float) * *rows);
        for (size_t i = 0; i < *rows; i++)
            for (size_t k = 0; k < *cols; k++)
                res[i] += mat[i][k] * vec[k];
    }
    return res;
}

float** mat_matSub(const size_t* rows, const size_t* cols, const float** mat1, const float** mat2) {
    float** res;
    if ((res = malloc(sizeof *res * *rows)) != NULL)
        for (size_t i = 0; i < *rows; i++)
            if ((res[i] = malloc(sizeof *res[i] * *cols)) != NULL)
                for (size_t j = 0; j < *cols; j++)
                    res[i][j] = mat1[i][j] - mat2[i][j];
    return res;
}

float* vec_vecSub(const size_t* rows, const float* vec1, const float* vec2, float* res) {
    if (res == NULL)
        res = malloc(sizeof(float) * *rows);
    if (res != NULL)
        for (size_t i = 0; i < *rows; i++)
            res[i] = vec1[i] - vec2[i];
    return res;
}

float* vec_vecAdd(const size_t* rows, const float* vec1, const float* vec2, float* res) {
    if (res == NULL)
        res = malloc(sizeof(float) * *rows);
    if (res != NULL)
        for (size_t i = 0; i < *rows; i++)
            res[i] = vec1[i] + vec2[i];
    return res;
}

void freeMat(const size_t* rows, float** mat) {
    for (size_t i = 0; i < *rows; i++)
        free(mat[i]);
    free(mat);
}

float** readMatrix(size_t* rows, size_t* cols, const char* filename) {
    if (rows == NULL || cols == NULL || filename == NULL)
        return NULL;

    *rows = 0, *cols = 0;
    FILE* fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "could not open %s: %s\n", filename, strerror(errno));
        return NULL;
    }

    float** matrix = NULL, ** tmp;
    char line[2048];

    while (fgets(line, sizeof(line), fp) && strcmp(line, "\n") != 0) { // if empty line, end of input
        if (*cols == 0) { // determine the size of the columns based on the first row
            char* scan = line;
            float dummy;
            int offset = 0;
            while (sscanf(scan, "%f%n", &dummy, &offset) == 1) {
                scan += offset;
                (*cols)++;
            }
        }
        if ((tmp = realloc(matrix, (*rows + 1) * sizeof *matrix)) == NULL) {
            fclose(fp);
            return matrix; // return all you've parsed so far
        }
        matrix = tmp;
        matrix[*rows] = calloc(*cols, sizeof *matrix[*rows]);
        if (matrix[*rows] == NULL) {
            fclose(fp);
            if (*rows == 0) { // failed in the first row, free everything
                free(matrix);
                return NULL;
            }
            return matrix; // return all you've parsed so far
        }

        int offset = 0;
        char* scan = line;
        for (size_t j = 0; j < *cols; ++j) {
            if (sscanf(scan, "%f%n", matrix[*rows] + j, &offset) == 1)
                scan += offset;
            else
                matrix[*rows][j] = 0; // could not read, set cell to 0
        } // incrementing rows
        (*rows)++;
    }
    fclose(fp);
    return matrix;
}

void printMatrix(const size_t* rows, const size_t* cols, float** mat) {
    for (size_t i = 0; i < *rows; ++i) {
        for (size_t j = 0; j < *cols; ++j)
            printf("%-10.4f ", mat[i][j]);
        puts("");
    }
    puts("");
}

void printVec(const char* entrance, const char* exit, const size_t* rows, const float* vec) {
    puts(entrance);
    for (size_t i = 0; i < *rows; i++)
        printf("%-14.8f", vec[i]);
    puts(exit);
}

void appendSolution(const size_t* rows, const float* solution, const char* filename) {
    FILE* fp;

    if ((fp = fopen(filename, "r+")) == NULL) {
        fprintf(stderr, "could not open %s: %s\n", filename, strerror(errno));
        return;
    }
    fseek(fp, 0, SEEK_END);

    char c = '\0';
    int count = -1;

    while (c != '\n') { // find the last empty line
        fread(&c, 1, 1, fp);
        fseek(fp, count--, SEEK_END);
    }

    fputs("\n\n", fp);
    for (size_t i = 0; i < *rows; i++)
        fprintf(fp, "%f ", solution[i]);
    fclose(fp);
}

float norm2(const size_t* rows, const float* vec) {
    float sum = 0;
    for (size_t i = 0; i < *rows; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
}

float* CGM(const float* precision, const size_t* rows, const size_t* cols, const float** mat, const float* b) {
    float* res = calloc(*rows, sizeof(float)); // filled with 0s
    float* tmp = mat_vecMul(res, rows, cols, mat, NULL), * q = NULL;
    float* e = vec_vecSub(rows, b, tmp, NULL), * p = malloc(sizeof(float) * *rows);
    memcpy(p, e, sizeof(float) * *rows);
    float alpha, beta;
    int k = 0;

    while (norm2(rows, e) > *precision && k++ < *rows) {
        q = mat_vecMul(p, rows, cols, mat, q);
        alpha = dotProduct(rows, e, p) / dotProduct(rows, q, p);
        res = vec_vecAdd(rows, res, sc_vecMul(&alpha, rows, p, tmp), res);
        e = vec_vecSub(rows, e, sc_vecMul(&alpha, rows, q, tmp), e);

        if (norm2(rows, e) <= *precision)
            break;

        beta = dotProduct(rows, e, q) / dotProduct(rows, p, q);
        p = vec_vecSub(rows, e, sc_vecMul(&beta, rows, p, tmp), p);
    }
    free(e);
    free(p);
    free(q);
    free(tmp);
    return res;
}