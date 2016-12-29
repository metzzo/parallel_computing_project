//
// Created by Robert Fischer on 05.12.16.
//

#include <string.h>
#include <stdlib.h>
#include "pthread_solution.h"
#include "assert.h"
#include "../definitions/shared.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

struct thread_info {
    pthread_t thread_id;

    int start_index, end_index;
    int index, p;

    sem_t *condMineTop, *condMineBottom;
    sem_t *condOtherTop, *condOtherBottom;

    pthread_mutex_t *debug_mutex;

    int hasOtherTop, hasOtherBottom;

    MATRIX_DATA *data;
    STENCIL *stencil;
};

void thread_print_matrix(struct thread_info *tinfo, char *info) {
    pthread_mutex_lock(tinfo->debug_mutex);

    DEBUG_LOG("Thread %d: %s\n", tinfo->index, info);
    print_matrix(tinfo->data);
    DEBUG_LOG("-----------------------------\n");

    pthread_mutex_unlock(tinfo->debug_mutex);
}

void thread_print_matrix_and_vector(struct thread_info *tinfo, INT_MATRIX vector, int vector_size, char *info) {
    pthread_mutex_lock(tinfo->debug_mutex);

    DEBUG_LOG("Thread %d: %s\n", tinfo->index, info);
    print_matrix(tinfo->data);
    DEBUG_LOG("Vector:\n");
    print_vector(vector, vector_size);
    DEBUG_LOG("----------------------------\n");

    pthread_mutex_unlock(tinfo->debug_mutex);
}

static void* calculate_submatrix(void *arg){
    struct thread_info *tinfo = arg;
    MATRIX_DATA *data = tinfo->data;
    INT_MATRIX matrix = data->matrix;

    INT_MATRIX last_row = malloc(sizeof(int) * (data->column_count + 2));
    INT_MATRIX current_row = malloc(sizeof(int) * (data->column_count + 2));

    INT_MATRIX top_row = malloc(sizeof(int) * data->column_count);
    INT_MATRIX bottom_row = malloc(sizeof(int) * data->column_count);


    for (int iteration = 0; iteration < tinfo->stencil->iteration_count; iteration++) {
        int values[3][3];
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++) {
                values[row][column] = get_matrix_value(row + tinfo->start_index, column, data);
            }
        }

        if (tinfo->start_index == 0) {
            memcpy(last_row, data->top, (data->column_count + 2) * sizeof(int));

            current_row[0] = data->left[0];
            memcpy(&current_row[1], data->matrix, data->column_count * sizeof(int));
            current_row[data->column_count + 1] = data->right[0];
        } else {
            last_row[0] = data->left[tinfo->start_index - 1];
            memcpy(&last_row[1], &matrix[MATRIX_POSITION(tinfo->start_index - 1, 0, data)], (data->column_count + 2) * sizeof(int));
            last_row[data->column_count + 1] = data->right[tinfo->start_index - 1];

            current_row[0] = data->left[tinfo->start_index];
            memcpy(&current_row[1], &data->matrix[MATRIX_POSITION(tinfo->start_index, 0, data)], data->column_count * sizeof(int));
            current_row[data->column_count + 1] = data->right[tinfo->start_index];
        }


        for (int row = tinfo->start_index; row < tinfo->end_index; row++) {
            for (int column = 0; column < data->column_count; column++) {
                int value = tinfo->stencil->stencil_func(values);
                if (row == tinfo->start_index) {
                    top_row[column] = value;
                } else if (row == tinfo->end_index - 1) {
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

            if (row == tinfo->start_index) {
                pthread_mutex_lock(tinfo->debug_mutex);
                DEBUG_LOG("CondMineTop Semaphore Post in Thread %d\n", tinfo->index);
                pthread_mutex_unlock(tinfo->debug_mutex);

                sem_post(tinfo->condMineTop);
            }

            if (row == tinfo->end_index - 1) {
                pthread_mutex_lock(tinfo->debug_mutex);
                DEBUG_LOG("CondMineBottom Semaphore Post in Thread %d\n", tinfo->index);
                pthread_mutex_unlock(tinfo->debug_mutex);

                sem_post(tinfo->condMineBottom);
            }
        }

        if (tinfo->hasOtherBottom) {
            pthread_mutex_lock(tinfo->debug_mutex);
            DEBUG_LOG("CondOtherBottom Semaphore Wait in Thread %d\n", tinfo->index);
            pthread_mutex_unlock(tinfo->debug_mutex);

            sem_wait(tinfo->condOtherBottom);
        }

        thread_print_matrix(tinfo, "Before copying bottom_row");

        memcpy(&data->matrix[MATRIX_POSITION((tinfo->end_index-1), 0, data)], &bottom_row[0], data->column_count * sizeof(int));

        if (tinfo->hasOtherTop) {
            pthread_mutex_lock(tinfo->debug_mutex);
            DEBUG_LOG("CondOtherTop Semaphore Wait in Thread %d\n", tinfo->index);
            pthread_mutex_unlock(tinfo->debug_mutex);

            sem_wait(tinfo->condOtherTop);
        }
        thread_print_matrix_and_vector(tinfo, bottom_row, data->column_count, "After copying bottom_row, before copying top_row");

        memcpy(&data->matrix[MATRIX_POSITION(tinfo->start_index, 0, data)], &top_row[0], data->column_count * sizeof(int));

        thread_print_matrix_and_vector(tinfo, top_row, data->column_count, "After copying top_row");
    }

    free(last_row);
    free(current_row);

    return NULL;
}

#define SEMAPHORE_NAME "aa_%d"

void stencil_pthread(MATRIX_DATA *data, STENCIL *stencil, int thread_count) {
    struct thread_info tinfo[thread_count];
    pthread_mutex_t debug_mutex;
    pthread_mutex_init(&debug_mutex, NULL);

    for (int i = 0; i < thread_count; i++) {
        tinfo[i].index = i;
        tinfo[i].p = thread_count;
        tinfo[i].start_index = data->column_count/thread_count * i;
        tinfo[i].end_index = data->column_count/thread_count * (i + 1);
        tinfo[i].data = data;
        tinfo[i].stencil = stencil;
        tinfo[i].hasOtherBottom = 0;
        tinfo[i].hasOtherTop = 0;
        tinfo[i].debug_mutex = &debug_mutex;

        char sem1[20], sem2[20];
        sprintf(&sem1[0], SEMAPHORE_NAME, i * 2);
        sprintf(&sem2[0], SEMAPHORE_NAME, i * 2 + 1);
        sem_unlink(sem1);
        sem_unlink(sem2);

        tinfo[i].condMineTop = sem_open(sem1, 0);
        tinfo[i].condMineBottom = sem_open(sem2, 0);
    }
    for (int i = 0; i < thread_count && thread_count > 1; i++) {
        if (i == thread_count - 1) {
            tinfo[i].condOtherTop = tinfo[i-1].condMineBottom;
            tinfo[i].hasOtherTop = 1;
        } else if (i == 0) {
            tinfo[i].condOtherBottom = tinfo[i+1].condMineTop;
            tinfo[i].hasOtherBottom = 1;
        } else {
            tinfo[i].condOtherBottom = tinfo[i-1].condMineTop;
            tinfo[i].condOtherTop = tinfo[i+1].condMineBottom;

            tinfo[i].hasOtherTop = 1;
            tinfo[i].hasOtherBottom = 1;
        }
    }
    for (int i = 0; i < thread_count; i++) {
        pthread_create(&tinfo[i].thread_id, NULL, &calculate_submatrix, &tinfo[i]);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(tinfo[i].thread_id, NULL);
    }

    for (int i = 0; i < thread_count; i++) {
        sem_close(tinfo[i].condMineBottom);
        sem_close(tinfo[i].condMineTop);

        char sem1[20], sem2[20];
        sprintf(&sem1[0], SEMAPHORE_NAME, i * 2);
        sprintf(&sem2[0], SEMAPHORE_NAME, i * 2 + 1);

        sem_unlink(sem1);
        sem_unlink(sem2);
    }
}