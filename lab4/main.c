#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "utils.h"
#include "invit.h"

int main(void) {
    size_t capacity = 0;
    char* dir_name = "./gen_files";
    char** filenames = readDir(dir_name, &capacity);
    char** filename = filenames;
    size_t cols, rows;

    int toleranses = 11;
    float* tols = malloc(sizeof(float) * toleranses);
    if (tols == NULL)
        return 1;
    for (int i = 0; i < toleranses; i++)
        tols[i] = pow(10, -i);

    while (*filename != NULL) {
        char* fname = malloc(sizeof(char) * strlen(*filename));
        strcpy(fname, *filename);
        strncpy(strstr(fname, "files"), "data/", 5);

        float** matrix = readMatrix(&rows, &cols, *filename++);
        if (matrix == NULL) {
            fprintf(stderr, "could not read matrix\n");
            freeFilenames(filenames, capacity);
            return 1;
        }

        float** LU = allocateMat(&rows, &rows);
        if (LU == NULL) {
            fprintf(stderr, "could not create LU matrix\n");
            freeFilenames(filenames, capacity);
            freeMat(&rows, matrix);
            return 1;
        }
        LUDooDec(LU, matrix, &rows);

        float* res = calloc(rows, sizeof(float));
        float* y = malloc(sizeof(float) * rows);
        for (size_t i = 0; i < rows; i++)
            y[i] = 1;
        float eig = 1.0;

        FILE* fp;
        if ((fp = fopen(fname, "a")) == NULL) {
            fprintf(stderr, "could not open file\n");
            freeFilenames(filenames, capacity);
            free(y);
            free(res);
            freeMat(&rows, LU);
            freeMat(&rows, matrix);
            return 1;
        }


        for (size_t i = 0; i < toleranses; i++) {
            SPInvIt(res, matrix, LU, y, &tols[i], &eig, &rows);

            printVec(res, &rows, "res:", "");
            fprintf(fp, "%13.11f %18.15f %d\n", tols[i], eig, getIters());
            printf("tol: %13.11f\n", tols[i]);
            printf("eig: %18.15f\n", eig);
            printf("iters: %d\n\n", getIters());
        }

        free(y);
        free(res);
        freeMat(&rows, LU);
        freeMat(&rows, matrix);
    }

    free(tols);
    freeFilenames(filenames, capacity
    );
    return 0;
}