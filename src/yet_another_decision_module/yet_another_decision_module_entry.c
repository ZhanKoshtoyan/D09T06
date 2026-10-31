#include <stdio.h>
#include <stdlib.h>

#include "data_io.h"
#include "decision.h"

int main() {
    int n;
    double *data;

    if (scanf("%d", &n) != 1) return 1;

    data = (double *)malloc(n * sizeof(double));
    if (data == NULL) return 1;

    input(data, n);

    if (make_decision(data, n)) {
        printf("YES");
    } else {
        printf("NO");
    }

    free(data);
    return 0;
}