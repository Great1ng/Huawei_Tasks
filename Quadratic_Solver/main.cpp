#include <stdio_ext.h>
#include "equations.h"
#include "unit_tests.h"

//#define TESTING

const int CORRECT_INPUT = 3;

void run_unit_tests();
void run_work_cycle();

int main() {

#ifdef TESTING
    run_unit_tests();
#else
    run_work_cycle();
#endif

    return EXIT_SUCCESS;
}

void run_unit_tests() {
    const int n_tests = 6;

    double inputs[n_tests][5] = {
            {1, 5, 6},
            {0, 1, 6},
            {0, 5, 0},
            {0, 0, 3},
            {0, 0, 0},
            {NAN, NAN, 1}
    };
    double outputs[n_tests][4] = {
            {2, -3, -2},
            {1, -6,  0},
            {1,  0,  0},
            {0,  0,  0},
            {EQ_ROOTS_INF},
            {EQ_ERROR_NOT_FINITE}
    };

    for (unsigned test = 0; test < n_tests; ++test) {
        UNIT_TEST_RESULT result = run_unit_test(inputs[test], outputs[test]);

        if (result == UNIT_TEST_RESULT::INPUT_ERROR)
            fprintf(stderr, "Test input error!\n");

        if (result == UNIT_TEST_RESULT::FAILED) {
            fprintf(stderr, "Test %u failed: ", test);
            fprintf(stderr, "Output %lg, %lg, %lg ", outputs[test][3], inputs[test][3], inputs[test][4]);
            fprintf(stderr, "Expected %lg, %lg, %lg\n", outputs[test][0], outputs[test][1], outputs[test][2]);
        }
    }
}

void run_work_cycle() {
    printf("# Quadratic equation solver\n"
           "# (c) Innokentiy Popov, 2021\n\n");

    double a = NAN, b = NAN, c = NAN;

    int input = 0;
    while (input != CORRECT_INPUT) {
        printf("Enter a, b, c: ");
        input = scanf("%lg %lg %lg", &a, &b, &c);
        __fpurge(stdin);

        if (input != CORRECT_INPUT)
            printf("Invalid input! Enter only number!\n");
    }

    double root_1 = 0, root_2 = 0;

    int number_of_roots = solve_quadratic(a, b, c, &root_1, &root_2);

    switch(number_of_roots)
    {
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
        case EQ_ERROR_NOT_FINITE:
            fprintf(stderr, "\nERROR: Input value is infinity or NaN!\n");
            break;
        case EQ_ERROR_EQUAL_PTR:
            fprintf(stderr, "\nERROR: The pointers are equal!\n");
            break;
        case EQ_ERROR_NULL_PTR:
            fprintf(stderr, "\nERROR: The pointer is null!\n");
            break;
        default:
            fprintf(stderr, "\nERROR: amount_of_roots = %d\n", number_of_roots);
            break;
    }
}
