#include <stdio.h>
#include <stdlib.h>

#include "data_io.h"
#include "data_process.h"

int main() {
    int n;
    double *data;

    if (scanf("%d", &n) != 1) return 1;

    data = (double *)malloc(n * sizeof(double));
    if (data == NULL) return 1;

    input(data, n);

    if (normalization(data, n)) {
        output(data, n);
    } else {
        printf("ERROR");
    }

    free(data);
    return 0;
}