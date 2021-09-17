#ifndef QUADRATIC_SOLVER_UNIT_TESTS_H
#define QUADRATIC_SOLVER_UNIT_TESTS_H

#include <stdio.h>
#include "equations.h"

//!< All possible unit test results
enum UNIT_TEST_RESULT {
    INPUT_ERROR = -1,
    FAILED = 0,
    PASSED = 1
};

//!------------------------------------------------------------
//! \brief Tests the solve_quadratic function
//! \param[in] input array of solve_quadratic inputs
//! \param[in] output array of solve_quadratic expected outputs
//! \return if test was passed PASSED, FAILED if failed
//!
//! \note return INPUT_ERROR when you pass invalid parametrs
//!------------------------------------------------------------
UNIT_TEST_RESULT run_unit_test (double input[5], double output[4]);

#endif //QUADRATIC_SOLVER_UNIT_TESTS_H
