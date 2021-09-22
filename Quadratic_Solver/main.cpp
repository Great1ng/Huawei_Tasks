#include <stdio_ext.h>
#include "equations.h"
#include "unit_tests.h"

//#define TESTING

void run_unit_tests();

void print_roots(int number_of_roots, double root_1, double root_2);

void print_error(int error_code);

void run_work_cycle();

int main() {

#ifdef TESTING
    run_unit_tests();
#else
    run_work_cycle();
#endif

    return 0;
}

void run_unit_tests() {
    const int n_tests = 6;

    const unit_test inputs[n_tests] = {
            {1, 5, 6, 2, -3, -2},
            {0, 1, 6, 1, -6},
            {0, 5, 0, 1, 0},
            {0, 0, 3, 0},
            {0, 0, 0, EQ_ROOTS_INF},
            {NAN, NAN, 1, EQ_ERROR_NOT_FINITE}
    };

    int n_roots = 0;
    double root_1 = NAN, root_2 = NAN;

    for (unsigned test = 0; test < n_tests; ++test) {
        UNIT_TEST_RESULT result = run_unit_test(&inputs[test], &n_roots, &root_1, &root_2);

        if (result == UNIT_TEST_RESULT::INPUT_ERROR)
            printf("Test input error!\n");

        if (result == UNIT_TEST_RESULT::FAILED) {
            printf("Test %u failed: ", test+1);
            printf("Output %d, %lg, %lg ", n_roots, root_1, root_2);
            printf("Expected %d, %lg, %lg\n", inputs[test].n_roots, inputs[test].root_1, inputs[test].root_2);
        }
    }
}

void print_roots(int number_of_roots, double root_1, double root_2) {
    switch(number_of_roots) {
        case EQ_ROOTS_ZERO:
            printf("no roots\n");
            break;
        case EQ_ROOTS_ONE:
            printf("only one root:\nx = %.9lg\n", root_1);
            break;
        case EQ_ROOTS_TWO:
            printf("two roots:\nx1 = %.9lg\nx2 = %.9lg\n", root_1, root_2);
            break;
        case EQ_ROOTS_INF:
            printf("infinitely many roots\n");
            break;
        default:
            printf("\nERROR: amount_of_roots = %d\n", number_of_roots);
    }
}

void print_error(int error_code) {
    switch(error_code) {
        case EQ_ERROR_NOT_FINITE:
            printf("\nERROR: Input value is infinity or NaN!\n");
            break;
        case EQ_ERROR_EQUAL_PTR:
            printf("\nERROR: The pointers are equal!\n");
            break;
        case EQ_ERROR_NULL_PTR:
            printf("\nERROR: The pointer is null!\n");
            break;
        default:
            printf("\nERROR: error_code = %d\n", error_code);
    }
}

void run_work_cycle() {
    printf("# Quadratic equation solver\n"
           "# (c) Innokentiy Popov, 2021\n\n");

    const int CORRECT_INPUT = 3;
    double a = NAN, b = NAN, c = NAN;

    int input = 0;
    while (input != CORRECT_INPUT) {
        printf("Enter a, b, c: ");
        input = scanf("%lg %lg %lg", &a, &b, &c);
        __fpurge(stdin);

        if (input != CORRECT_INPUT)
            printf("Invalid input! Enter only number!\n");
    }

    double root_1 = NAN, root_2 = NAN;

    int number_of_roots = solve_quadratic(a, b, c, &root_1, &root_2);

    if (number_of_roots < 0)
        print_error(number_of_roots);
    else
        print_roots(number_of_roots, root_1, root_2);
}
