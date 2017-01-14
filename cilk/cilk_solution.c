//
// Created by Robert Fischer on 31.12.16.
//

#include <cilk/cilk.h>

#include <string.h>
#include <stdlib.h>
#include <sys/param.h>
#include "cilk_solution.h"
#include "assert.h"
#include "../definitions/shared.h"

typedef struct cilk_info {
    int start_index, end_index;
    INT_MATRIX top_row, bottom_row;
    INT_MATRIX last_row, current_row;

    MATRIX_DATA *data;
    STENCIL *stencil;
} CILK_INFO;

void stencil_calculator(CILK_INFO *info) {
    MATRIX_DATA *data = info->data;

    INT_MATRIX top_row = info->top_row;
    INT_MATRIX bottom_row = info->bottom_row;

    INT_MATRIX last_row = info->last_row;
    INT_MATRIX current_row = info->current_row;

    int values[3][3];
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            values[row][column] = get_matrix_value(row + info->start_index, column, data);
        }
    }

    if (info->start_index == 0) {
        memcpy(last_row, data->top, (data->column_count + 2) * sizeof(int));

        current_row[0] = data->left[0];
        memcpy(&current_row[1], data->matrix, data->column_count * sizeof(int));
        current_row[data->column_count + 1] = data->right[0];
    } else {
        last_row[0] = data->left[info->start_index - 1];
        memcpy(&last_row[1], &data->matrix[MATRIX_POSITION(info->start_index - 1, 0, data)],
               data->column_count * sizeof(int));
        last_row[data->column_count + 1] = data->right[info->start_index - 1];

        current_row[0] = data->left[info->start_index];
        memcpy(&current_row[1], &data->matrix[MATRIX_POSITION(info->start_index, 0, data)],
               data->column_count * sizeof(int));
        current_row[data->column_count + 1] = data->right[info->start_index];
    }


    for (int row = info->start_index; row < info->end_index; row++) {
        for (int column = 0; column < data->column_count; column++) {
            int value = info->stencil->stencil_func(values);
            if (row == info->start_index) {
                top_row[column] = value;
            } else if (row == info->end_index - 1) {
                bottom_row[column] = value;
            } else {
                data->matrix[MATRIX_POSITION(row, column, data)] = value;
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

        if (row < info->end_index - 1) {
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
}

void stencil_writer(CILK_INFO *info) {
    MATRIX_DATA *data = info->data;

    if (info->end_index - 1 != info->start_index) {
        memcpy(&data->matrix[MATRIX_POSITION((info->end_index - 1), 0, data)], &info->bottom_row[0],
               data->column_count * sizeof(int));
    }
    memcpy(&data->matrix[MATRIX_POSITION(info->start_index, 0, data)], &info->top_row[0],
           data->column_count * sizeof(int));
}



void stencil_cilk(MATRIX_DATA *data, STENCIL *stencil, int thread_count) {
    thread_count = MIN(thread_count, data->row_count);

    CILK_INFO infos[thread_count];

    for (int thread_num = 0; thread_num < thread_count; thread_num++) {
        infos[thread_num].start_index = data->row_count / thread_count * thread_num;
        infos[thread_num].end_index = data->row_count / thread_count * (thread_num + 1);

        if (thread_count == thread_num + 1) {
            infos[thread_num].end_index = data->row_count;
        }

        infos[thread_num].last_row = malloc(sizeof(int) * (data->column_count + 2));
        infos[thread_num].current_row = malloc(sizeof(int) * (data->column_count + 2));

        infos[thread_num].top_row = malloc(sizeof(int) * data->column_count);
        infos[thread_num].bottom_row = malloc(sizeof(int) * data->column_count);

        infos[thread_num].data = data;
        infos[thread_num].stencil = stencil;
    }

    for (int iteration = 0; iteration < stencil->iteration_count; iteration++) {
        for (int thread_num = 0; thread_num < thread_count; thread_num++) {
            cilk_spawn stencil_calculator(&infos[thread_num]);
        }
        cilk_sync;

        for (int thread_num = 0; thread_num < thread_count; thread_num++) {
            cilk_spawn stencil_writer(&infos[thread_num]);
        }
        cilk_sync;
    }

    for (int thread_num = 0; thread_num < thread_count; thread_num++) {
        free(infos[thread_num].last_row);
        free(infos[thread_num].current_row);

        free(infos[thread_num].top_row);
        free(infos[thread_num].bottom_row);
    }
}