//
// Created by Robert Fischer on 29.12.16.
//

#include <string.h>
#include "../../definitions/shared.h"
#include "../test_runner.h"


void test_simple_matrix(int thread_count) {
    const int matrix_size = 4*4;

    int input_matrix1[] = {
            1,2,3,4,
            2,3,4,5,
            3,4,5,6,
            4,5,6,7
    };

    int input_matrix2[matrix_size];
    memcpy(&input_matrix2, input_matrix1, sizeof(int) * matrix_size);

    BOUNDARY boundaries_top_bottom = (int[6]) {1,2,3,4,5,6};
    BOUNDARY boundaries_left_right = (int[4]) {5,6,7,8};

    MATRIX_DATA datas1 = {
            input_matrix1, 4, 4,
            boundaries_top_bottom,
            boundaries_top_bottom,
            boundaries_left_right,
            boundaries_left_right
    };

    MATRIX_DATA datas2 = {
            input_matrix2, 4, 4,
            boundaries_top_bottom,
            boundaries_top_bottom,
            boundaries_left_right,
            boundaries_left_right
    };


    STENCIL stencils = {
            &add_stencil_func,
            1
    };

    int output_matrix[] = {
            25, 24, 33, 42,
            33, 27, 36, 45,
            42, 36, 45, 54,
            37, 36, 45, 54
    };

    MATRIX_DATA expected_datas = {
            output_matrix, 4, 4,
            boundaries_top_bottom,
            boundaries_top_bottom,
            boundaries_left_right,
            boundaries_left_right
    };

    printf("Sequential Implementation\n");
    stencil_sequential(&datas1, &stencils);
    check_equal(&datas1, &expected_datas);

    printf("pThread Implementation\n");
    stencil_pthread(&datas2, &stencils, thread_count);
    check_equal(&datas2, &expected_datas);
}