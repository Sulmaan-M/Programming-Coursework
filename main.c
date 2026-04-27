#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

int main() {
    int row = 0;
    const char* filename = "power_quality_log.csv";
    const char* output_filename = "results.txt";

    WaveformSample* data = load_csv_file(filename, &row);

    double rms_voltage[3];
    double peak_to_peak[3];
    double dc_offset[3];
    int clipped_results[3];

    calculate_rms_voltage(data, row, rms_voltage);
    calculate_peak_to_peak(data, row, peak_to_peak);
    calculate_dc_offset(data, row, dc_offset);
    detect_clipping(data, row, clipped_results);

    char phase_voltages[3] = {'A', 'B', 'C'};

    for (int i = 0; i < 3; i++) {
        printf("PHASE %c Results:\n", phase_voltages[i]);
        printf("  RMS Voltage      : %.2lf V\n", rms_voltage[i]);
        printf("  Peak-to-Peak     : %.2lf V\n", peak_to_peak[i]);
        printf("  DC Offset        : %.2lf V\n", dc_offset[i]);
        printf("  Clipped Samples  : %d\n", clipped_results[i]);

        if (check_tolerance(rms_voltage[i]) == 1) {
            printf("PASS (Within 10%% of 230V)\n\n");
        } else {
            printf("FAIL (Out of bounds)\n\n");
        }
    }

    export_results_to_file(output_filename, rms_voltage, peak_to_peak, dc_offset, clipped_results);

    free(data);

    system("notepad results.txt");

    return 0;
}