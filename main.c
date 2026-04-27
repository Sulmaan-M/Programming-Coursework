    #include <stdio.h>
    #include <stdlib.h>
    #include "io.h"

    int main() {

        int row = 0;
        char* filename = "power_quality_log.csv";

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
            check_tolerance(rms_voltage[i]);
        }


        free(data);

        return 0;

    }