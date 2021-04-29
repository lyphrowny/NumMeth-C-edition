#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "lab2.h"

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

void freeMatrix(const size_t* rows, float** mat) {
    for (size_t i = 0; i < *rows; ++i)
        free(mat[i]);
    free(mat);
}

void rotate(const size_t* rows, const size_t* cols, float** mat) {
    float s, c, divider;
    size_t curr_col = 0;
    for (size_t i = 0; i < *rows - 1; i++, curr_col++) {
        for (size_t i_1 = i + 1; i_1 < *rows; i_1++) {
            float (* two_rows)[*cols] = malloc(sizeof(*two_rows) * 2);
            divider = sqrt(pow(mat[i][curr_col], 2) + pow(mat[i_1][curr_col], 2));
            c = mat[i][curr_col] / divider, s = mat[i_1][curr_col] / divider;
            for (size_t j = 0; j < *cols; j++) {
                two_rows[0][j] = c * mat[i][j] + s * mat[i_1][j];
                two_rows[1][j] = -s * mat[i][j] + c * mat[i_1][j];
            }
            memcpy(mat[i], two_rows[0], sizeof(two_rows[0]));
            memcpy(mat[i_1], two_rows[1], sizeof(two_rows[1]));
            free(two_rows);
        }
    }
}

float* reverse(const size_t* rows, const size_t* cols, float** mat) {
    float* xs = malloc(sizeof(float) * *rows);
    float sum;
    for (size_t j = *cols - 2; j < *cols; j--) { // -2 since -1 is Bs
        sum = 0;
        for (size_t s = j + 1; s < *cols - 1; s++)
            sum += mat[j][s] * xs[s];
        xs[j] = 1 / mat[j][j] * (mat[j][*cols - 1] /* b */ - sum);
    }
    return xs;
}

float norm(const size_t* rows, float* vec) {
    double sum = 0;
    for (size_t i = 0; i < *rows; i++)
        sum += pow(vec[i], 2);
    return sqrt(sum);
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