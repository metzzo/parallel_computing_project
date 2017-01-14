//
// Created by Robert Fischer on 14.01.17.
//

#ifndef PROJECT_TEST_GENERATOR_H
#define PROJECT_TEST_GENERATOR_H

#include "../definitions/shared.h"

MATRIX_DATA* generate_big_matrix(int row_count, int column_count);

MATRIX_DATA* generate_constant_matrix(int row_count, int column_count);
MATRIX_DATA* generate_constant_expected_matrix(int row_count, int column_count, int iteration_count);

MATRIX_DATA* generate_simple_matrix();
MATRIX_DATA* generate_simple_expected_matrix();


#endif //PROJECT_TEST_GENERATOR_H
