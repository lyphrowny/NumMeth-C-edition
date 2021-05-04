#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <errno.h>

#include "lab3.h"

void freeMat(const size_t* rows, float** mat) {
    for (size_t i = 0; i < *rows; i++)
        free(mat[i]);
    free(mat);
}

void freeFilenames(char** filenames, size_t capacity) {
    for (size_t i = 0; i < capacity; i++)
        free(filenames[i]);
    free(filenames);
}

char** readDir(const char* dir_name, size_t* capacity) {
    struct dirent* dp;
    DIR* dir = opendir(dir_name);
    *capacity = 10;
    size_t curr = 0;
    char** filenames = (char**) calloc(*capacity, sizeof(char*));
    // Unable to open directory stream
    if (!dir) {
        fprintf(stderr, "could not read directory: %s\n", strerror(errno));
        free(filenames);
        return NULL;
    }
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            if (curr >= *capacity - 1) {
                *capacity <<= 1;
                filenames = (char**) realloc(filenames, *capacity * (sizeof(char*)));
            }
            size_t str_size = sizeof(dp->d_name) + sizeof(char*) * (strlen(dir_name) + 1);
            filenames[curr] = (char*) malloc(str_size);
            sprintf(filenames[curr++], "%s/%s", dir_name, dp->d_name);
        }
    }
    filenames[curr] = NULL;
    // Close directory stream
    closedir(dir);

    return filenames;
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

void printMat(const float** mat, const size_t* rows, const size_t* cols) {
    for (size_t i = 0; i < *rows; ++i) {
        for (size_t j = 0; j < *cols; ++j)
            printf("%-10.4f ", mat[i][j]);
        puts("");
    }
    puts("");
}

void printVec(const float* vec, const size_t* rows, const char* entrance, const char* exit) {
    puts(entrance);
    for (size_t i = 0; i < *rows; ++i)
        printf("%-10.4f ", vec[i]);
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