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

rewind(file);

    fgets(row_counter, sizeof(row_counter), file);

    for (int i = 0; i < count; i++) {
        if (fgets(row_counter, sizeof(row_counter), file) != NULL) {

            sscanf(row_counter, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                   &memory_allocation[i].timestamp,
                   &memory_allocation[i].phase_A_voltage,
                   &memory_allocation[i].phase_B_voltage,
                   &memory_allocation[i].phase_C_voltage,
                   &memory_allocation[i].line_current,
                   &memory_allocation[i].frequency,
                   &memory_allocation[i].power_factor,
                   &memory_allocation[i].thd_percent);
        }
    }
        fclose(file);

    return memory_allocation;
}