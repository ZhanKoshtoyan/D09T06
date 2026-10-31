#include <stdio.h>
#include <stdlib.h>

#include "data_io.h"
#include "data_process.h"
#include "data_stat.h"
#include "decision.h"

int main() {
    int n;
    double *data;
    int decision;

    if (scanf("%d", &n) != 1) return 1;
    data = (double *)malloc(n * sizeof(double));
    if (data == NULL) return 1;

    printf("LOAD DATA...\n");
    input(data, n);

    decision = make_decision(data, n);

    printf("RAW DATA:\n\t");
    output(data, n);
    printf("\n");

    if (!normalization(data, n)) {
        printf("ERROR\n");
        free(data);
        return 1;
    }

    printf("NORMALIZED DATA:\n\t");
    output(data, n);
    printf("\n");

    sort(data, n);
    printf("SORTED NORMALIZED DATA:\n\t");
    output(data, n);
    printf("\n");

    printf("FINAL DECISION:\n\t");
    printf("%s\n", decision ? "YES" : "NO");

    free(data);
    return 0;
}