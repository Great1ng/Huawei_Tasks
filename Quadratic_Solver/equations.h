#ifndef QUADRATIC_SOLVER_EQUATIONS_H
#define QUADRATIC_SOLVER_EQUATIONS_H

#include <math.h>
#include "utils.h"

//!< All possible roots equations return
enum EQ_ROOTS {
    EQ_ROOTS_ZERO = 0,
    EQ_ROOTS_ONE = 1,
    EQ_ROOTS_TWO = 2,
    EQ_ROOTS_INF = 3
};

//! All possible errors equations return
enum EQ_ERROR {
    EQ_ERROR_NOT_FINITE = -1,
    EQ_ERROR_EQUAL_PTR = -2,
    EQ_ERROR_NULL_PTR = -3
};

//!-------------------------------------------------------------------------------
//! \brief Solves quadratic equation ax^2 + bx + c = 0
//!
//! \param [in] a a-coefficient
//! \param [in] b b-coefficient
//! \param [in] c c-coefficient
//! \param [out] root_1 Pointer to the first root
//! \param [out] root_2 Pointer to the second root
//! \return Number of roots
//!
//! \note In case of infinitely many number of roots return SQ_INF_ROOTS
//!-------------------------------------------------------------------------------
int solve_quadratic(const double a, const double b, const double c, double* root_1, double* root_2);

//!-------------------------------------------------------------------------------
//! \brief Solves linear equation ax + b = 0
//!
//! \param [in] a a-coefficient
//! \param [in] b b-coefficient
//! \param [out] root Pointer to the root
//! \return Number of roots
//!
//! \note In case of infinitely many number of roots return SQ_INF_ROOTS
//!-------------------------------------------------------------------------------
int solve_linear(const double a, const double b, double* root);

#endif //QUADRATIC_SOLVER_EQUATIONS_H
