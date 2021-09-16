#ifndef QUADRATIC_SOLVER_UTILS_H
#define QUADRATIC_SOLVER_UTILS_H

#include <math.h>

//!-----------------------------------------------------------
//! \brief Compares two double numbers with accuracy UTILS_EPS
//!
//! \param [in] x Number that is compared
//! \param [in] y Number you compare with
//! \return If absolute value of x-y is less than UTILS_EPS
//!-----------------------------------------------------------
int compare(const double x, const double y);

#endif //QUADRATIC_SOLVER_UTILS_H
