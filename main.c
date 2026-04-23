#include <stdio.h>
#include "io.h"

int main() {

 int load_data = load_csv_file("power_quality_log.csv");

 if (load_data !=0) {
     printf("Row test failed\n");
 }

    return 0;
}