//
// Created by Robert Fischer on 05.12.16.
//

#ifndef PROJECT_TEST_RUNNER_H
#define PROJECT_TEST_RUNNER_H

#include "../sequential/sequential_solution.h"
#include "../pthread/pthread_solution.h"
#include "../openmp/openmp_solution.h"

void check_equal(MATRIX_DATA *a, MATRIX_DATA *b);
int add_stencil_func(int values[3][3]);
int increment_stencil_func(int values[3][3]);

#endif //PROJECT_TEST_RUNNER_H
