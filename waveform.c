#include <stdio.h>
#include <math.h>
#include "waveform.h"

double calculate_rms_voltage(WaveformSample *data, int rows) {

    double sum_of_squares_Phase_A = 0.0;

    for (int i = 0; i < rows; i++) {
        double current_voltage_Phase_A = data[i].phase_A_voltage;

        sum_of_squares_Phase_A += (current_voltage_Phase_A * current_voltage_Phase_A);
    }

    double mean_square = sum_of_squares_Phase_A / rows;
    return sqrt(mean_square);

}

double calculate_peak_to_peak (WaveformSample *data, int rows) {

    double max_voltage = data [0].phase_A_voltage;
    double min_voltage = data [0].phase_A_voltage;

    for (int i = 0; i < rows; i++){

        double current_voltage = data [i].phase_A_voltage;

        if (current_voltage > max_voltage) {
            max_voltage = current_voltage;

        }

        if (current_voltage < min_voltage) {
           min_voltage = current_voltage;
}
    }
         return (max_voltage - min_voltage);
}

double calculate_dc_offset(WaveformSample *data, int rows) {

    double sum = 0.0;

    for (int i = 0; i < rows; i++) {
        sum += data[i].phase_A_voltage;
    }
    return sum / (double) rows;
}

int detect_clipping(WaveformSample *data, int rows) {
    int count = 0;

    for (int i = 0; i < rows; i++) {
        if (fabs(data[i].phase_A_voltage)>=324.9) {
            count++;
        }
    }

    return count;
}

int check_tolerance(double rms_voltage) {

    if (rms_voltage >= 207.0 && rms_voltage <= 253.0) {
        return 1;
    }
     return 0;
}
