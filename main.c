#include <stdio.h>
#include <stdlib.h> // FIX: This is needed for free()
#include "io.h"

int main() {

    int row = 0;
    char* filename = "power_quality_log.csv";

    WaveformSample* data = load_csv_file(filename, &row);

        printf ("Row test\n");

        printf("Row 0 | time %lf | phase A: %lf\n", data[0].timestamp, data[0].phase_A_voltage);
        printf("Row 1 | time %lf | phase A: %lf\n", data[1].timestamp, data[1].phase_A_voltage);
        printf("Row 2 | time %lf | phase A: %lf\n", data[2].timestamp, data[2].phase_A_voltage);


           free(data);


    return 0;
}