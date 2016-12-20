//
// Created by Robert Fischer on 05.12.16.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "test_runner.h"
#include "../sequential/sequential.h"
#include "../pthread/pthread_solution.h"

int add_stencil_func(int values[3][3]) {
    int result = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result += values[i][j];
        }
    }
    return result;
}

int increment_stencil_func(int values[3][3]) {
    return values[1][1] + 1;
}


int main(int argc, char **args) {
    INT_MATRIX input_matrix1 = (int[4*4]) {
            1,2,3,4,
            2,3,4,5,
            3,4,5,6,
            4,5,6,7
    };
    INT_MATRIX input_matrix2 = (int[4*4]) {
            1,2,3,4,
            2,3,4,5,
            3,4,5,6,
            4,5,6,7
    };
    INT_MATRIX input_matrix3 = (int[4*4]) {
            1,2,3,4,
            2,3,4,5,
            3,4,5,6,
            4,5,6,7
    };
    INT_MATRIX input_matrix4 = (int[4*4]) {
            1,2,3,4,
            2,3,4,5,
            3,4,5,6,
            4,5,6,7
    };
    BOUNDARY boundaries_top_bottom = (int[6]) {1,2,3,4,5,6};
    BOUNDARY boundaries_left_right = (int[4]) {5,6,7,8};

    MATRIX_DATA datas1[] = {
            {
                    input_matrix1, 4, 4,
                    boundaries_top_bottom,
                    boundaries_top_bottom,
                    boundaries_left_right,
                    boundaries_left_right
            },
            {
                    input_matrix2, 4, 4,
                    boundaries_top_bottom,
                    boundaries_top_bottom,
                    boundaries_left_right,
                    boundaries_left_right
            }
    };
    MATRIX_DATA datas2[] = {
            {
                    input_matrix3, 4, 4,
                    boundaries_top_bottom,
                    boundaries_top_bottom,
                    boundaries_left_right,
                    boundaries_left_right
            },
            {
                    input_matrix4, 4, 4,
                    boundaries_top_bottom,
                    boundaries_top_bottom,
                    boundaries_left_right,
                    boundaries_left_right
            }
    };


    STENCIL stencils[] = {
            {
                &add_stencil_func,
                1
            },
            {
                &increment_stencil_func,
                1
            }
    };

    INT_MATRIX output_matrix1 = (int[4 * 4]) {
            25, 24, 33, 42,
            33, 27, 36, 45,
            42, 36, 45, 54,
            37, 36, 45, 54
    };

    INT_MATRIX output_matrix2 = (int[4 * 4]) {
            1+1,2+1,3+1,4+1,
            2+1,3+1,4+1,5+1,
            3+1,4+1,5+1,6+1,
            4+1,5+1,6+1,7+1
    };

    MATRIX_DATA expected_datas[] = {
            {
                    output_matrix1, 4, 4,
                    boundaries_top_bottom,
                    boundaries_top_bottom,
                    boundaries_left_right,
                    boundaries_left_right
            },
            {
                    output_matrix2, 4, 4,
                    boundaries_top_bottom,
                    boundaries_top_bottom,
                    boundaries_left_right,
                    boundaries_left_right
            }
    };

    // TODO: do not reuse memory for different tests

    //printf("Sequential Testing \n");
    //test_sequential(datas1, stencils, expected_datas);
    //printf("Success Sequential \n");

    printf("pthread Testing \n");
    test_pthread(datas2, stencils, expected_datas);
    printf("Success pthread \n");

    printf("TEST\n");
    //test_big_matrix(100, 100, 4, 4);
    printf("All tests finished successfully\n");

    return 0;
}

void test_big_matrix(int row_count, int column_count, int p, int iteration_count) {
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


    stencil_sequential(&data2, &stencil);
    stencil_pthread(&data1, &stencil, p);

    check_equal(&data1, &data2);
}

void check_equal(MATRIX_DATA *a, MATRIX_DATA *b) {
    assert(a != NULL);
    assert(b != NULL);
    assert(a->column_count == b->column_count);
    assert(a->row_count == b->row_count);

    for (int i = 0; i < a->row_count; i++) {
        for (int j = 0; j < a->column_count; j++) {
            assert(a->matrix[MATRIX_POSITION(i, j, a)] == b->matrix[MATRIX_POSITION(i, j, b)]);
        }
    }

    for (int i = 0; i < a->column_count + 2; i++) {
        assert(a->top[i] == b->top[i]);
        assert(a->bottom[i] == b->bottom[i]);
    }

    for (int i = 0; i < a->row_count; i++) {
        assert(a->left[i] == b->left[i]);
        assert(a->right[i] == b->right[i]);
    }
}

void test_sequential(MATRIX_DATA *datas, STENCIL *stencils, MATRIX_DATA *expected_datas) {
    assert(ARRAY_SIZE(&datas) == ARRAY_SIZE(&stencils));
    assert(ARRAY_SIZE(&stencils) == ARRAY_SIZE(&expected_datas));

    for (int i = 0; i < ARRAY_SIZE(&datas); i++) {
        printf("Sequential: Testing test case %d \n", i);
        stencil_sequential(&datas[i], &stencils[i]);
        check_equal(&datas[i], &expected_datas[i]);
        printf("Sequential: Test case %d finished successfully \n", i);
    }
}


void test_pthread(MATRIX_DATA *datas, STENCIL *stencils, MATRIX_DATA *expected_datas) {
    assert(ARRAY_SIZE(&datas) == ARRAY_SIZE(&stencils));
    assert(ARRAY_SIZE(&stencils) == ARRAY_SIZE(&expected_datas));

    for (int i = 0; i < ARRAY_SIZE(&datas); i++) {
        printf("PThread: Testing test case %d \n", i);
        stencil_pthread(&datas[i], &stencils[i], 4);
        check_equal(&datas[i], &expected_datas[i]);
        printf("PThread: Test case %d finished successfully \n", i);
    }
}
