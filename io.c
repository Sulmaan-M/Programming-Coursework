#include <stdio.h>
#include "io.h"
#include <stdlib.h>
#include "waveform.h"

WaveformSample* load_csv_file(char* filename, int* total_rowcount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return NULL;
    }

    char row_counter[1024];
    int count = 0;
    fgets(row_counter, sizeof(row_counter), file);
    while (fgets(row_counter, sizeof(row_counter), file) != NULL) {
        count++;
    }
    *total_rowcount = count;

    size_t row_size = sizeof(WaveformSample);
    size_t total_memory = count * row_size;
    WaveformSample *memory_allocation = (WaveformSample*) malloc (total_memory);


    if (memory_allocation == NULL) {
        printf("Error: memory not allocated\n");
        fclose(file);
        return NULL;
    }

    printf("Total number of rows found: %d rows of data.\n", count);
    printf("Size of one WaveformSample: %zu bytes\n", row_size);
    printf("Total memory to allocate: %zu bytes\n", total_memory);

    fclose(file);

    return memory_allocation;
}