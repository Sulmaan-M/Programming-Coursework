#include <stdio.h>
#include "io.h"
#include <stdlib.h>
#include "waveform.h"

WaveformSample* load_csv_file(const char* filename, int* total_rowcount) {
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

    WaveformSample *memory_allocation = (WaveformSample*) malloc(count * sizeof(WaveformSample));

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

void export_results_to_file(const char* filename, double* rms, double* ptp, double* dc, int* clip) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create the save file.\n");
        return;
    }

    char phases[3] = {'A', 'B', 'C'};
    fprintf(file, "3-PHASE POWER QUALITY ANALYSIS\n\n");

    for (int i = 0; i < 3; i++) {
        fprintf(file, "PHASE %c Results:\n", phases[i]);
        fprintf(file, "  RMS Voltage      : %.2lf V\n", rms);
        fprintf(file, "  Peak-to-Peak     : %.2lf V\n", ptp);
        fprintf(file, "  DC Offset        : %.2lf V\n", dc);
        fprintf(file, "  Clipped Samples  : %d\n", clip);

        if (check_tolerance(rms) == 1) {
            fprintf(file, "PASS (Within 10%% of 230V)\n\n");
        } else {
            fprintf(file, "FAIL (Out of bounds)\n\n");
        }
    }
    fclose(file);
    printf("SUCCESS: Results saved to %s\n", filename);
}