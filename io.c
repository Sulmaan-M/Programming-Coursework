#include <stdio.h>
#include "io.h"

int load_csv_file(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    printf("Success file was found\n");

    fclose(file);
}