#include "unit_tests.h"

UNIT_TEST_RESULT run_unit_test (double inputs[3], double expects[3], double outputs[3]) {
    if (inputs == NULL || expects == NULL || outputs == NULL)
        return UNIT_TEST_RESULT::INPUT_ERROR;

    outputs[0] = solve_quadratic(inputs[0], inputs[1], inputs[2], outputs+1, outputs+2);

    if ((int)outputs[0] != (int)expects[0])
        return UNIT_TEST_RESULT::FAILED;

    if (expects[0] < 1) return UNIT_TEST_RESULT::PASSED;
    if (!compare(outputs[1], expects[1]))
        return UNIT_TEST_RESULT::FAILED;

    if (expects[0] < 2) return UNIT_TEST_RESULT::PASSED;
    if (!compare(outputs[2], expects[2]))
        return UNIT_TEST_RESULT::FAILED;

    return UNIT_TEST_RESULT::PASSED;
}