#include "decision.h"

#include <math.h>

#include "data_stat.h"

int make_decision(const double *data, int n) {
    double m = mean(data, n);
    double sigma = sqrt(variance(data, n));
    double max_value = max(data, n);
    double min_value = min(data, n);

    // Проверка правила трёх сигм и условия на среднее
    int result = (max_value <= m + 3 * sigma) && (min_value >= m - 3 * sigma) && (m >= GOLDEN_RATIO);
    return result ? 1 : 0;
}