#include "equations.h"

int solve_quadratic(const double a, const double b, const double c, double* root_1, double* root_2) {
    if (!isfinite(a)) return EQ_ERROR_NOT_FINITE;
    if (!isfinite(b)) return EQ_ERROR_NOT_FINITE;
    if (!isfinite(c)) return EQ_ERROR_NOT_FINITE;

    if (root_1 == root_2) return EQ_ERROR_EQUAL_PTR;
    if (root_1 == NULL)   return EQ_ERROR_NULL_PTR;
    if (root_2 == NULL)   return EQ_ERROR_NULL_PTR;

    if (compare(a, 0))
        return solve_linear(b, c, root_1);

    const double dscr = b*b - 4*a*c;

    if (dscr < 0)
        return EQ_ROOTS_ZERO;

    if (compare(dscr, 0)) {
        *root_1 = -b / (2*a);
        return EQ_ROOTS_ONE;
    }

    const double sqrt_of_dscr = sqrt(dscr);
    *root_1 = (-b - sqrt_of_dscr) / (2*a);
    *root_2 = (-b + sqrt_of_dscr) / (2*a);
    return EQ_ROOTS_TWO;
}

int solve_linear(const double a, const double b, double* root) {
    if (!isfinite(a)) return EQ_ERROR_NOT_FINITE;
    if (!isfinite(b)) return EQ_ERROR_NOT_FINITE;

    if (root == NULL) return EQ_ERROR_NULL_PTR;

    if (compare(a, 0)) {
        if (compare(b, 0)) {
            return EQ_ROOTS_INF;
        }
        return EQ_ROOTS_ZERO;
    }

    *root = -b / a;
    return EQ_ROOTS_ONE;
}