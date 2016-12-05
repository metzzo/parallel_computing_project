//
// Created by Robert Fischer on 05.12.16.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "test_runner.h"
#include "../sequential/sequential.h"
#include "../definitions/shared.h"

int add_stencil_func(int values[3][3]) {
    int result = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result += values[i][j];
        }
    }
    return result;
}

int main(int argc, char **args) {
    printf("Sequential Testing \n");

    INT_MATRIX input_matrix = (int[4*4]) {
            1,2,3,4,
            2,3,4,5,
            3,4,5,6,
            4,5,6,7
    };
    BOUNDARY boundaries_top_bottom = (int[6]) {1,2,3,4,5,6};
    BOUNDARY boundaries_left_right = (int[4]) {5,6,7,8};

    MATRIX_DATA datas[] = {
            {
                    input_matrix, 4, 4,
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
            }
    };

    INT_MATRIX output_matrix = (int[4 * 4]) {
            25, 24, 33, 42,
            33, 27, 36, 45,
            42, 36, 45, 54,
            37, 36, 45, 54
    };

    MATRIX_DATA expected_datas[] = {
            {
                    output_matrix, 4, 4,
                    boundaries_top_bottom,
                    boundaries_top_bottom,
                    boundaries_left_right,
                    boundaries_left_right
            }
    };

    test_sequential(datas, stencils, expected_datas);

    printf("Success");

    return 0;
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
        stencil_sequential(&datas[i], &stencils[i]);
        check_equal(&datas[i], &expected_datas[i]);
    }
}
