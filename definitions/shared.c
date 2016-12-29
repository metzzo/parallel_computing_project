#include <printf.h>
#include "shared.h"
#include "assert.h"

int get_matrix_value(int row, int column, MATRIX_DATA *data) {
    assert(row >= 0);
    assert(column >= 0);
    assert(row < data->row_count + 2);
    assert(row < data->column_count + 2);

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
            DEBUG_LOG("%d\t", data->matrix[MATRIX_POSITION(row, column, data)]);
        }
        DEBUG_LOG("\n");
    }
    DEBUG_LOG("\n");
}

void print_vector(INT_MATRIX data, int vector_size) {
    for (int row = 0; row < vector_size; row++) {
        DEBUG_LOG("%d\t", data[row]);
    }
    DEBUG_LOG("\n");
}
