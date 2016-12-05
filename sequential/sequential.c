//
// Created by Robert Fischer on 05.12.16.
//

#include <string.h>
#include <stdlib.h>
#include "sequential.h"
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

int stencil_sequential(MATRIX_DATA *data, STENCIL *stencil) {
    INT_MATRIX matrix = data->matrix;

    for (int iteration = 0; iteration < stencil->iteration_count; iteration++) {
        int values[3][3];
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++) {
                values[row][column] = get_matrix_value(row, column, data);
            }
        }

        INT_MATRIX last_row = malloc(sizeof(int) * (data->column_count + 2));
        memcpy(last_row, data->top, (data->column_count + 2)*sizeof(int));

        INT_MATRIX current_row = malloc(sizeof(int) * (data->column_count + 2));
        current_row[0] = data->left[0];
        memcpy(&current_row[1], data->matrix, data->column_count * sizeof(int));
        current_row[data->column_count + 1] = data->right[0];

        for (int row = 0; row < data->row_count; row++) {
            for (int column = 0; column < data->column_count; column++) {
                matrix[MATRIX_POSITION(row, column, data)] = stencil->stencil_func(values);

                if (column < data->column_count - 1) {
                    values[0][0] = last_row[column + 1];
                    values[0][1] = last_row[column + 2];
                    values[0][2] = last_row[column + 3];

                    values[1][0] = values[1][1];
                    values[1][1] = values[1][2];
                    values[1][2] = get_matrix_value(row + 1, column + 3, data);

                    values[2][0] = values[2][1];
                    values[2][1] = values[2][2];
                    values[2][2] = get_matrix_value(row + 2, column + 3, data);
                }
            }

            if (row < data->row_count - 1) {
                values[0][0] = current_row[0];
                values[0][1] = current_row[1];
                values[0][2] = current_row[2];

                values[1][0] = get_matrix_value(row + 2, 0, data);
                values[1][1] = get_matrix_value(row + 2, 1, data);
                values[1][2] = get_matrix_value(row + 2, 2, data);

                values[2][0] = get_matrix_value(row + 3, 0, data);
                values[2][1] = get_matrix_value(row + 3, 1, data);
                values[2][2] = get_matrix_value(row + 3, 2, data);

                INT_MATRIX tmp = last_row;
                last_row = current_row;
                current_row = tmp;

                current_row[0] = data->left[row + 1];
                memcpy(&current_row[1], &data->matrix[MATRIX_POSITION(row + 1, 0, data)], data->column_count * sizeof(int));
                current_row[data->column_count + 1] = data->right[row + 1];
            }
        }

        free(last_row);
        free(current_row);
    }
}