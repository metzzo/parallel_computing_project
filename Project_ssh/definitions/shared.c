#include <printf.h>
#include <stdlib.h>
#include "shared.h"
#include "assert.h"
#include <sys/time.h>

int get_matrix_value(int row, int column, MATRIX_DATA *data) {
    assert(row >= 0);
    assert(column >= 0);
    assert(row < data->row_count + 2);
    assert(column < data->column_count + 2);

    if (row == 0) {
        return data->top[column];
    } else if (row == data->row_count + 1) {
        return data->bottom[column];
    } else if (column == 0) {
        return data->left[row - 1];
    } else if (column == data->column_count + 1) {
        return data->right[row - 1];
    } else {
        return data->matrix[MATRIX_POSITION(row - 1, column - 1, data)];
    }
}


void print_matrix(MATRIX_DATA *data) {
    for (int row = 0; row < data->row_count; row++) {
        for (int column = 0; column < data->column_count; column++) {
            printf("%d\t", data->matrix[MATRIX_POSITION(row, column, data)]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_vector(INT_MATRIX data, int vector_size) {
    for (int row = 0; row < vector_size; row++) {
        printf("%d\t", data[row]);
    }
    printf("\n");
}


void free_matrixdata(MATRIX_DATA *data) {
    if (data == NULL) {
        return;
    }

    if (data->top == data->bottom) {
        failsafe_free((void**)&data->top);
    } else {
        failsafe_free((void**)&data->top);
        failsafe_free((void**)&data->bottom);
    }

    if (data->left == data->right) {
        failsafe_free((void**)&data->left);
    } else {
        failsafe_free((void**)&data->left);
        failsafe_free((void**)&data->right);
    }

    failsafe_free((void**)&data->matrix);
    failsafe_free((void**)&data);
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
    //printf("Check equal was successful <3\n");
}

void failsafe_free(void ** ptr) {
    if (ptr == NULL) {
        return;
    }

    if (ptr[0] != NULL) {
        free(ptr[0]);
    }
    ptr[0] = NULL;
}

double mytime(void) {
    struct timeval now; gettimeofday(&now,NULL);
    return (double)((long long)now.tv_usec+
                    (long long)now.tv_sec*1000000) / 1000.0;
}