#include "data_stat.h"

double max(const double *data, int n) {
    double m = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] > m) m = data[i];
    }
    return m;
}

double min(const double *data, int n) {
    double m = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] < m) m = data[i];
    }
    return m;
}

double mean(const double *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += data[i];
    return sum / n;
}

double variance(const double *data, int n) {
    double m = mean(data, n);
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double diff = data[i] - m;
        sum += diff * diff;
    }
    return sum / n;
}

void sort(double *data, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                double tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}