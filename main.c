#include <stdio.h>

int main () {

    FILE* file = fopen ("power_quality_log.csv", "r");

    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    printf("Success file was found\n");

    fclose(file);

    return 0;
}