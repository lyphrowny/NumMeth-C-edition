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

    int toleranses = 15;
    double* tols = malloc(sizeof(double) * toleranses);
    if (tols == NULL)
        return 1;
    for (int i = 0; i < toleranses; i++)
        tols[i] = pow(10, -i);

    while (*filename != NULL) {
        char* fname = malloc(sizeof(char) * (strlen(*filename) + 1));
        strcpy(fname, *filename);
        strncpy(strstr(fname, "files"), "data/", 5);

        double** matrix = readMatrix(&rows, &cols, *filename++);
        if (matrix == NULL) {
            fprintf(stderr, "could not read matrix\n");
            freeFilenames(filenames, capacity);
            return 1;
        }

        double** LU = allocateMat(&rows, &rows);
        if (LU == NULL) {
            fprintf(stderr, "could not create LU matrix\n");
            freeFilenames(filenames, capacity);
            freeMat(&rows, matrix);
            return 1;
        }
        puts(fname);
        LUDooDec(LU, matrix, &rows);

        double* res = calloc(rows, sizeof(double));
        double* y = malloc(sizeof(double) * rows);

        FILE* fp;
        if ((fp = fopen(fname, "w")) == NULL) {
            fprintf(stderr, "could not open file\n");
            freeFilenames(filenames, capacity);
            free(y);
            free(res);
            freeMat(&rows, LU);
            freeMat(&rows, matrix);
            return 1;
        }

        double eig;
        for (size_t i = 0; i < toleranses; i++) {
            for (size_t j = 0; j < rows; j++)
                y[j] = 1;
            eig = 1.0;
            SPInvIt(res, matrix, LU, y, &tols[i], &eig, &rows);

            printVec(res, &rows, "res:", "");
            fprintf(fp, "%17.15f %20.18f %d\n", tols[i], eig, getIters());
            printf("tol: %17.15f\n", tols[i]);
            printf("eig: %20.18f\n", eig);
            printf("iters: %d\n\n", getIters());
        }

        free(fname);
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