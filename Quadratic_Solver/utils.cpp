#include "utils.h"

const double UTILS_EPS = 1e-16;

int compare(const double x, const double y) {
    return fabs(x - y) < UTILS_EPS;
}