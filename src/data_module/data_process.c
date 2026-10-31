#include "data_process.h"

#include <math.h>

#include "data_stat.h"

int normalization(double *data, int n) {
    double max_value = max(data, n);
    double min_value = min(data, n);
    double size = max_value - min_value;
    int result = 0;

    if (fabs(size) >= EPS) {
        for (int i = 0; i < n; ++i) {
            data[i] = (data[i] - min_value) / size;
        }
        result = 1;
    }
    return result;
}