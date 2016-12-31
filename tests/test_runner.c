//
// Created by Robert Fischer on 05.12.16.
//

#include <stdio.h>
#include <assert.h>

#include "../definitions/shared.h"

#include "test_runner.h"

#include "test_cases/test_big_matrix.h"
#include "test_cases/test_simple_matrix.h"
#include "test_cases/test_constant_matrix.h"

int main(int argc, char **args) {
    printf("---------------------------------------\n");
    printf("Test Constant Matrix \n");
    for (int row_count = 1; row_count < 20; row_count++) {
        for (int column_count = 1; column_count < 20; column_count++) {
            printf("... with size row_count: %d column_count: %d\n", row_count, column_count);
            for (int thread_count = 1; thread_count < 20; thread_count++) {
                printf("... with thread_count %d\n", thread_count);
                test_constant_matrix(row_count, column_count, thread_count, 4);
            }
        }
    }

    printf("Success Constant Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Simple Matrix \n");
    test_simple_matrix(2);
    printf("Success Simple Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Big Matrix\n");
    test_big_matrix(4, 4, 1, 1);
    printf("Success Big Matrix\n");

    printf("---------------------------------------\n");
    printf("All tests finished successfully\n");

    return 0;
}

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

void check_equal(MATRIX_DATA *a, MATRIX_DATA *b) {
    assert(a != NULL);
    assert(b != NULL);
    assert(a->column_count == b->column_count);
    assert(a->row_count == b->row_count);

    for (int i = 0; i < a->row_count; i++) {
        for (int j = 0; j < a->column_count; j++) {
            if (a->matrix[MATRIX_POSITION(i, j, a)] != b->matrix[MATRIX_POSITION(i, j, b)]) {
                printf("check_equal failed\n---------------------------------------\n");

                fprintf(stderr, "Row %d, Column %d, a[row,column] = %d, b[row, column] = %d\n", i, j,
                        a->matrix[MATRIX_POSITION(i, j, a)], b->matrix[MATRIX_POSITION(i, j, b)]);

                printf("Matrix a:\n");
                print_matrix(a);

                printf("Matrix b:\n");
                print_matrix(b);

                assert(0 && "Matrix a and b are not the same.");
            }
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