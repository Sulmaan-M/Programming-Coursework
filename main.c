#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int main() {

    int row = 0;
    char* filename = "power_quality_log.csv";

    WaveformSample* data = load_csv_file(filename, &row);

        double rms_voltage = calculate_rms_voltage(data, row);

        printf("Phase A RMS Voltage: %.2lf V\n", rms_voltage);

    free(data);

    return 0;

}