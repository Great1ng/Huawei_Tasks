#include "unit_tests.h"

UNIT_TEST_RESULT run_unit_test (int (*function)(double, double, double, double*, double*), double input[5], double output[4]) {
    if (input == NULL || output == NULL || function == NULL)
        return UNIT_TEST_RESULT::INPUT_ERROR;

    int result = function(input[0], input[1], input[2], input+3, input+4);

    if (result != (int)output[0]) {
        output[3] = result;
        return UNIT_TEST_RESULT::FAILED;
    }

    if (!compare(output[1], input[3]))
        return UNIT_TEST_RESULT::FAILED;

    if (!compare(output[2], input[4]))
        return UNIT_TEST_RESULT::FAILED;

    return UNIT_TEST_RESULT::PASSED;
}