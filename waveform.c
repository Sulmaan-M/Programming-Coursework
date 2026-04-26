#include <stdio.h>
#include <math.h>
#include "waveform.h"

double calculate_rms_voltage(WaveformSample *data, int rows) {

    double sum_of_squares = 0.0;

    for (int i = 0; i < rows; i++) {
        double current_voltage = data[i].phase_A_voltage;
        sum_of_squares += (current_voltage * current_voltage);
    }

    double mean_square = sum_of_squares / rows;
    return sqrt(mean_square);

}

double calculate_peak_to_peak (WaveformSample *data, int rows) {

    double max_voltage = data [0].phase_A_voltage;
    double min_voltage = data [0].phase_A_voltage;

    for (int i = 1; i < rows; i++){

        double current_voltage = data [i].phase_A_voltage;

        if (current_voltage > max_voltage) {
            max_voltage = current_voltage;

        }

        if current_voltage < min_voltage) {
           min_voltage = current_voltage;
}
    }
         return (max_voltage - min_voltage);
}