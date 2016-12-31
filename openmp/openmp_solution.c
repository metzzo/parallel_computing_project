//
// Created by Robert Fischer on 31.12.16.
//

#include <libiomp/omp.h>

#include <string.h>
#include <stdlib.h>
#include "openmp_solution.h"
#include "assert.h"
#include "../definitions/shared.h"
#include <sys/param.h>


void stencil_openmp(MATRIX_DATA *data, STENCIL *stencil) {
#pragma omp parallel num_threads(MIN(omp_get_max_threads(), data->row_count))
    {
        int num_threads = omp_get_num_threads();
        int thread_num = omp_get_thread_num();

        int start_index = data->row_count / num_threads * thread_num;
        int end_index = data->row_count / num_threads * (thread_num + 1);

        if (num_threads == thread_num + 1) {
            end_index = data->row_count;
        }

        INT_MATRIX matrix = data->matrix;

        INT_MATRIX last_row = malloc(sizeof(int) * (data->column_count + 2));
        INT_MATRIX current_row = malloc(sizeof(int) * (data->column_count + 2));

        INT_MATRIX top_row = malloc(sizeof(int) * data->column_count);
        INT_MATRIX bottom_row = malloc(sizeof(int) * data->column_count);


        for (int iteration = 0; iteration < stencil->iteration_count; iteration++) {
            int values[3][3];
            for (int row = 0; row < 3; row++) {
                for (int column = 0; column < 3; column++) {
                    values[row][column] = get_matrix_value(row + start_index, column, data);
                }
            }

            if (start_index == 0) {
                memcpy(last_row, data->top, (data->column_count + 2) * sizeof(int));

                current_row[0] = data->left[0];
                memcpy(&current_row[1], data->matrix, data->column_count * sizeof(int));
                current_row[data->column_count + 1] = data->right[0];
            } else {
                last_row[0] = data->left[start_index - 1];
                memcpy(&last_row[1], &matrix[MATRIX_POSITION(start_index - 1, 0, data)],
                       data->column_count * sizeof(int));
                last_row[data->column_count + 1] = data->right[start_index - 1];

                current_row[0] = data->left[start_index];
                memcpy(&current_row[1], &data->matrix[MATRIX_POSITION(start_index, 0, data)],
                       data->column_count * sizeof(int));
                current_row[data->column_count + 1] = data->right[start_index];
            }


            for (int row = start_index; row < end_index; row++) {
                for (int column = 0; column < data->column_count; column++) {
                    int value = stencil->stencil_func(values);
                    if (row == start_index) {
                        top_row[column] = value;
                    } else if (row == end_index - 1) {
                        bottom_row[column] = value;
                    } else {
                        matrix[MATRIX_POSITION(row, column, data)] = value;
                    }

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

                if (row < end_index - 1) {
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
                    memcpy(&current_row[1], &data->matrix[MATRIX_POSITION(row + 1, 0, data)],
                           data->column_count * sizeof(int));
                    current_row[data->column_count + 1] = data->right[row + 1];
                }
            }

#pragma omp barrier
            memcpy(&data->matrix[MATRIX_POSITION((end_index - 1), 0, data)], &bottom_row[0],
                   data->column_count * sizeof(int));

            memcpy(&data->matrix[MATRIX_POSITION(start_index, 0, data)], &top_row[0],
                   data->column_count * sizeof(int));
#pragma omp barrier
        }

        free(last_row);
        free(current_row);

        free(top_row);
        free(bottom_row);
    }
}