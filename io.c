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
        printf("Header row ignored successfully.\n");
    }

    while (fgets(row_counter, sizeof(row_counter), file) !=NULL){
        count++; //increase row count by 1
    }

    printf("Total number of rows found: %d rows of data.\n", count);

fclose(file);

    return count;
}