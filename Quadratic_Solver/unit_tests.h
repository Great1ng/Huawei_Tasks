#ifndef QUADRATIC_SOLVER_UNIT_TESTS_H
#define QUADRATIC_SOLVER_UNIT_TESTS_H

#include <stdio.h>
#include "equations.h"

enum UNIT_TEST_RESULT {
    INPUT_ERROR = -1,
    FAILED = 0,
    PASSED = 1
};

UNIT_TEST_RESULT run_unit_test (int (*function)(double, double, double, double*, double*), double input[5], double output[4]);

#endif //QUADRATIC_SOLVER_UNIT_TESTS_H
