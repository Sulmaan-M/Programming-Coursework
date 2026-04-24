#include <stdio.h>
#include <stdlib.h> // FIX: This is needed for free()
#include "io.h"

int main() {

    int final_row_count = 0;
    char* filename = "power_quality_log.csv";

    WaveformSample* data_array = load_csv_file(filename, &final_row_count);

        free(data_array);

    return 0;
}