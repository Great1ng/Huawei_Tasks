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
//! \param[in] inputs array of solve_quadratic inputs
//! \param[in] expects array of solve_quadratic expected outputs
//! \param[out] outputs array of solve_duadratic outputs
//! \return if test was passed PASSED, FAILED if failed
//!
//! \note return INPUT_ERROR when you pass invalid parametrs
//!------------------------------------------------------------
UNIT_TEST_RESULT run_unit_test (double inputs[3], double expects[3], double outputs[3]);

#endif //QUADRATIC_SOLVER_UNIT_TESTS_H
