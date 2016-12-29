//
// Created by Robert Fischer on 05.12.16.
//

#include <stdio.h>
#include <assert.h>

#include "../definitions/shared.h"

#include "test_runner.h"

#include "test_cases/test_big_matrix.h"
#include "test_cases/test_simple_matrix.h"

int main(int argc, char **args) {
    printf("Test Simple Matrix \n");
    test_simple_matrix(4);
    printf("Success pthread \n");

    printf("Test Big Matrix\n");
    test_big_matrix(100, 100, 4, 4);
    printf("Success Big Matrix\n");

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


