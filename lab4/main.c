#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <dirent.h>
#include <errno.h>

#include "utils.h"
#include "revit.h"

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
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
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
        float** matrix = readMatrix(&rows, &cols, filenames[filename]);
        if (matrix == NULL) {
            fprintf(stderr, "could not read matrix\n");
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
    for (size_t i = 0; i < curr; i++)
        free(filenames[i]);
    free(filenames);
    return 0;
}