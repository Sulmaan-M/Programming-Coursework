#include <stdio.h>
#include <math.h>
#include "waveform.h"

void calculate_rms_voltage(WaveformSample *data, int rows, double *results) {

    double sum_of_squares_Phase_A = 0.0;
    double sum_of_squares_Phase_B = 0.0;
    double sum_of_squares_Phase_C = 0.0;

    for (int i = 0; i < rows; i++) {
        double current_voltage_Phase_A = data[i].phase_A_voltage;
        double current_voltage_Phase_B = data[i].phase_B_voltage;
        double current_voltage_Phase_C = data[i].phase_C_voltage;

        sum_of_squares_Phase_A += (current_voltage_Phase_A * current_voltage_Phase_A);
        sum_of_squares_Phase_B += (current_voltage_Phase_B * current_voltage_Phase_B);
        sum_of_squares_Phase_C += (current_voltage_Phase_C * current_voltage_Phase_C);
    }

    results[0] = sqrt(sum_of_squares_Phase_A / rows);
    results[1] = sqrt(sum_of_squares_Phase_B / rows);
    results[2] = sqrt(sum_of_squares_Phase_C / rows);
}

void calculate_peak_to_peak(WaveformSample *data, int rows, double *results) {

    double max_A = data[0].phase_A_voltage, min_A = data[0].phase_A_voltage;
    double max_B = data[0].phase_B_voltage, min_B = data[0].phase_B_voltage;
    double max_C = data[0].phase_C_voltage, min_C = data[0].phase_C_voltage;

    for (int i = 0; i < rows; i++) {

        if (data[i].phase_A_voltage > max_A) max_A = data[i].phase_A_voltage;
        if (data[i].phase_A_voltage < min_A) min_A = data[i].phase_A_voltage;

        if (data[i].phase_B_voltage > max_B) max_B = data[i].phase_B_voltage;
        if (data[i].phase_B_voltage < min_B) min_B = data[i].phase_B_voltage;

        if (data[i].phase_C_voltage > max_C) max_C = data[i].phase_C_voltage;
        if (data[i].phase_C_voltage < min_C) min_C = data[i].phase_C_voltage;
    }

    results[0] = max_A - min_A;
    results[1] = max_B - min_B;
    results[2] = max_C - min_C;
}

void calculate_dc_offset(WaveformSample *data, int rows, double *results) {
    double sum_A = 0.0, sum_B = 0.0, sum_C = 0.0;

    for (int i = 0; i < rows; i++) {
        sum_A += data[i].phase_A_voltage;
        sum_B += data[i].phase_B_voltage;
        sum_C += data[i].phase_C_voltage;
    }

    results[0] = sum_A / rows;
    results[1] = sum_B / rows;
    results[2] = sum_C / rows;
}

void detect_clipping(WaveformSample *data, int rows, int *results) {

    results[0] = 0;
    results[1] = 0;
    results[2] = 0;

    for (int i = 0; i < rows; i++) {
        if (fabs(data[i].phase_A_voltage) >= 324.9) results[0]++;
        if (fabs(data[i].phase_B_voltage) >= 324.9) results[1]++;
        if (fabs(data[i].phase_C_voltage) >= 324.9) results[2]++;
    }
}

    int check_tolerance(double rms_voltage) {
    if (rms_voltage >= 207.0 && rms_voltage <= 253.0) {
        return 1;
    }
    return 0;
}