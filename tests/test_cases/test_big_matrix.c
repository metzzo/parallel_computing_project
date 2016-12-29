//
// Created by Robert Fischer on 29.12.16.
//

#include <string.h>
#include <stdlib.h>
#include "../../definitions/shared.h"
#include "../test_runner.h"

void test_big_matrix(int row_count, int column_count, int thread_count, int iteration_count) {
    int input_matrix_1[row_count * column_count];
    int boundaries_top_bottom[row_count + 2];
    int boundaries_left_right[column_count];

    int input_matrix_2[row_count * column_count];

    for (int row = 0; row < row_count; row++) {
        for (int column = 0; column < column_count; column++) {
            input_matrix_1[row * column_count + column] = input_matrix_2[row * column_count + column] = rand();
        }
    }

    for (int row = 0; row + 2 < row_count; row++) {
        boundaries_top_bottom[row] = rand();
    }
    for (int column = 0; column < column_count; column++) {
        boundaries_left_right[column] = rand();
    }


    MATRIX_DATA data1 = {
            input_matrix_1,
            column_count,
            row_count,
            boundaries_top_bottom,
            boundaries_top_bottom,
            boundaries_left_right,
            boundaries_left_right
    };

    MATRIX_DATA data2 = {
            input_matrix_2,
            column_count,
            row_count,
            boundaries_top_bottom,
            boundaries_top_bottom,
            boundaries_left_right,
            boundaries_left_right
    };

    STENCIL stencil = {
            &add_stencil_func,
            iteration_count
    };

    printf("Sequential Implementation \n");
    stencil_sequential(&data2, &stencil);

    printf("pThread Implementation \n");
    stencil_pthread(&data1, &stencil, thread_count);

    check_equal(&data1, &data2);
}