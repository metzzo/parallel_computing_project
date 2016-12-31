//
// Created by Robert Fischer on 29.12.16.
//

#include <string.h>
#include <stdlib.h>
#include "../../definitions/shared.h"
#include "../test_runner.h"

void test_big_matrix(int row_count, int column_count, int thread_count, int iteration_count) {
    int input_matrix_1[row_count * column_count];
    int input_matrix_2[row_count * column_count];
    int input_matrix_3[row_count * column_count];
    int input_matrix_4[row_count * column_count];

    int boundaries_top_bottom[row_count + 2];
    int boundaries_left_right[column_count];



    for (int row = 0; row < row_count; row++) {
        for (int column = 0; column < column_count; column++) {
            input_matrix_1[row * column_count + column] =
            input_matrix_2[row * column_count + column] =
            input_matrix_3[row * column_count + column] =
            input_matrix_4[row * column_count + column] = 1; //rand() % 100;
        }
    }

    for (int column = 0; column < column_count + 2; column++) {
        boundaries_top_bottom[column] = 1; //rand() % 100;
    }
    for (int row = 0; row < row_count; row++) {
        boundaries_left_right[row] = 1; //rand() % 100;
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

    MATRIX_DATA data3 = {
            input_matrix_3,
            column_count,
            row_count,
            boundaries_top_bottom,
            boundaries_top_bottom,
            boundaries_left_right,
            boundaries_left_right
    };

    MATRIX_DATA data4 = {
            input_matrix_4,
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
    start_timer();
    stencil_sequential(&data1, &stencil);
    end_timer("Sequential");

    printf("pThread Implementation \n");
    start_timer();
    stencil_pthread(&data2, &stencil, thread_count);
    end_timer("pThread");

    printf("OpenMP Implementation \n");
    start_timer();
    stencil_openmp(&data3, &stencil);
    end_timer("OpenMP");

    printf("Cilk Implementation \n");
    start_timer();
    stencil_cilk(&data4, &stencil, thread_count);
    end_timer("Cilk");

    check_equal(&data1, &data2);
    check_equal(&data1, &data3);
    check_equal(&data1, &data4);
}