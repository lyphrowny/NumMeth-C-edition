#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "lab3.h"

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