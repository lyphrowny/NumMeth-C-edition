#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "utils.h"
#include "revit.h"

int main(void) {
    size_t capacity = 0;
    char** filenames = readDir("./gen_files", &capacity);
    char** filename = filenames;
    size_t cols, rows;

    while (*filename++ != NULL) {
        float** matrix = readMatrix(&rows, &cols, *filename);//[filename]);
        if (matrix == NULL) {
            fprintf(stderr, "could not read matrix\n");
            freeFilenames(filenames, capacity);
            return 1;
        }
        float b[rows];
        cols--;
        for (size_t i = 0; i < rows; i++)
            b[i] = matrix[i][cols];

        float* res = calloc(rows, sizeof(float));;

        // actual work

        free(res);
        cols++;
        freeMat(&rows, matrix);
    }
    freeFilenames(filenames, capacity);
    return 0;
}