#include "unit_tests.h"

UNIT_TEST_RESULT run_unit_test (const unit_test* input, int* n_roots, double* root_1, double* root_2) {
    if (input   == NULL) return UNIT_TEST_RESULT::INPUT_ERROR;
    if (n_roots == NULL) return UNIT_TEST_RESULT::INPUT_ERROR;
    if (root_1  == NULL) return UNIT_TEST_RESULT::INPUT_ERROR;
    if (root_2  == NULL) return UNIT_TEST_RESULT::INPUT_ERROR;
    if (root_1  == root_2) return UNIT_TEST_RESULT::INPUT_ERROR;

    *n_roots = solve_quadratic(input->a, input->b, input->c, root_1, root_2);

    if (*n_roots != input->n_roots)
        return UNIT_TEST_RESULT::FAILED;

    if (input->n_roots == EQ_ROOTS_ONE) {
        if (!compare(*root_1, input->root_1))
            return UNIT_TEST_RESULT::FAILED;
    }

    if (input->n_roots == EQ_ROOTS_TWO) {
        if (!compare(*root_1, input->root_1))
            return UNIT_TEST_RESULT::FAILED;
        if (!compare(*root_2, input->root_2))
            return UNIT_TEST_RESULT::FAILED;
    }

    return UNIT_TEST_RESULT::PASSED;
}