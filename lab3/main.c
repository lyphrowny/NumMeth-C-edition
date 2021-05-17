#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <dirent.h>
#include <errno.h>

#include "lab3.h"
#include "conj.h"

int main(void) {

    struct dirent* dp;
    const char* dir_name = "./gen_files";
    DIR* dir = opendir(dir_name);
    size_t capacity = 10, curr = 0;
    char** filenames = (char**) malloc(capacity * sizeof(char*));
    // Unable to open directory stream
    if (!dir) {
        fprintf(stderr, "could not read directory: %s\n", strerror(errno));
        return 1;
    }
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, "gen_mat.txt") == 0) {
            if (curr >= capacity) {
                capacity <<= 1;
                filenames = (char**) realloc(filenames, capacity * (sizeof(char*)));
            }
            size_t str_size = sizeof(dp->d_name) + sizeof(char*) * (strlen(dir_name) + 1);
            filenames[curr] = (char*) malloc(str_size);
            char path[str_size];
            sprintf(path, "%s/%s", dir_name, dp->d_name);
            strcpy(filenames[curr++], path);
        }
    }
    // Close directory stream
    closedir(dir);

    size_t cols, rows;

    for (size_t filename = 0; filename < curr; filename++) {
        double** matrix = readMatrix(&rows, &cols, filenames[filename]);
        if (matrix == NULL) {
            fprintf(stderr, "could not read matrix\n");
            return 1;
        }

        double b[rows];
        cols--;
        for (size_t i = 0; i < rows; i++)
            b[i] = matrix[i][cols];

        printMatrix(&rows, &cols, matrix);

        double* res = calloc(rows, sizeof(double));;
        double precision = 0.1;
        double param[] = {0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 0.7, 0.8, 0.9, 1., 1.1, 1.2, 1.3, 1.4, 1.5};
        FILE* fp;
        if ((fp = fopen("./gen_data/sols.txt", "w")) != NULL) {
            for (size_t i = 0; i < sizeof(param) / sizeof(param[0]); i++) {
                matrix[rows - 1][rows - 1] = param[i];
                CGM(res, matrix, b, &precision, &rows);
                fprintf(fp, "%-10.5f", param[i]);
                for (size_t j = 0; j < rows; j++)
                    fprintf(fp, "%-20.8f", res[j]);
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
        if ((fp = fopen("./gen_data/prec.txt", "w")) != NULL) {
            for (size_t i = 0; i < 16; i++) {
                CGM(res, matrix, b, &precision, &rows);
                fprintf(fp, "%-20.17f %-5zu\n", precision, getIters());
                precision /= 10;
            }
        }
        fclose(fp);

        free(res);
        cols++;
        freeMat(&rows, matrix);
    }
    for (size_t i = 0; i < curr; i++)
        free(filenames[i]);
    free(filenames);
    return 0;
}