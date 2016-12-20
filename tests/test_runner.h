//
// Created by Robert Fischer on 05.12.16.
//

#ifndef PROJECT_TEST_RUNNER_H
#define PROJECT_TEST_RUNNER_H

#include "../definitions/shared.h"

void test_sequential(MATRIX_DATA datas[], STENCIL stencils[], MATRIX_DATA expected_datas[]);
void test_pthread(MATRIX_DATA *datas, STENCIL *stencils, MATRIX_DATA *expected_datas);
void check_equal(MATRIX_DATA *a, MATRIX_DATA *b);
void test_big_matrix(int row_count, int column_count, int p, int iteration_count);

#endif //PROJECT_TEST_RUNNER_H
