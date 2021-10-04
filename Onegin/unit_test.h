#ifndef ONEGIN_UNIT_TEST_H
#define ONEGIN_UNIT_TEST_H

#include "wide_text.h"
#include "sorting.h"

//!< All possible unit test results
enum UNIT_TEST_RESULT {
    ERROR_ON_RUN = -1,
    FAILED = 0,
    PASSED = 1
};

struct unit_test {
    const char* buffer;
    size_t length;
    comparison_type type;
};

//!------------------------------------------------------------
//! \brief Tests the mergesort function
//! \param[in] input Pointer on text to sort
//! \param[in] size Size of text to sort
//! \param[out] cmp_type Comparison type
//! \return If test was passed PASSED, FAILED if failed
//!
//! \note return ERROR_ON_RUN when something goes wrong
//!------------------------------------------------------------
UNIT_TEST_RESULT run_unit_test (unit_test* input, const wchar_t* expect)
__nonnull((1,4));

#endif //ONEGIN_UNIT_TEST_H
