    #include <stdio.h>
    #include <stdlib.h>
    #include "io.h"

    int main() {

        int row = 0;
        char* filename = "power_quality_log.csv";

        WaveformSample* data = load_csv_file(filename, &row);

            double rms_voltage = calculate_rms_voltage(data, row);
            double peak_to_peak = calculate_peak_to_peak(data, row);
            double dc_offset = calculate_dc_offset(data, row);
            int clipping_detection = detect_clipping(data, row);
            int tolerance = check_tolerance(rms_voltage);



            printf("Phase A RMS Voltage: %.2lf V\n", rms_voltage);
            printf("phase A Peak-to-Peak %.2lf\n", peak_to_peak);
            printf("Phase A DC Offet: %.2lf\n",dc_offset);
            printf("Phase A Clipping detection: %d\n", clipping_detection);

            if (tolerance == 1){

                printf("Phase A is compliant\n");
            }

            else {
                printf("Phase A is out of bounds\n");
            }

        free(data);

        return 0;

    }