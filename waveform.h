#ifndef waveform_h
#define waveform_h

typedef struct {

    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} WaveformSample;

double calculate_rms_voltage(WaveformSample *data, int rows);

double calculate_peak_to_peak(WaveformSample *data, int rows);

double calculate_dc_offset(WaveformSample *data, int rows);

int detect_clipping(WaveformSample *data, int rows);

int check_tolerance(double rms_voltage);

#endif