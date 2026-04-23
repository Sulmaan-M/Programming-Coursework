#include <stdio.h>
#include "io.h"

int load_csv_file(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1; //error code if file not found
    }

    char row_counter[1024];
    int count = 0;


    if (fgets(row_counter, sizeof (row_counter), file) !=NULL) {
        printf("Header row called: %s\n", row_counter);
    }

    if (fgets(row_counter, sizeof (row_counter), file)!=NULL){
        printf("next row test: %s\n", row_counter);
    }

fclose(file);

    return 0;
}