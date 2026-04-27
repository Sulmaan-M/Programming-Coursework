#ifndef io_h
#define io_h
#include "waveform.h"

WaveformSample* load_csv_file(const char* filename, int* total_rowcount);

void export_results_to_file(const char* filename, double* rms, double* ptp, double* dc, int* clip);

#endif
