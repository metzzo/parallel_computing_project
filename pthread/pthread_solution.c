//
// Created by Robert Fischer on 05.12.16.
//

#include <string.h>
#include <stdlib.h>
#include "pthread_solution.h"
#include "assert.h"
#include "pthread_barrier_osx.h"
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define THREAD_DEBUG_LOG(info, fmt, ...) if (DEBUG_MODE) { do {pthread_mutex_lock(tinfo->debug_mutex); DEBUG_LOG(fmt, ##__VA_ARGS__); pthread_mutex_unlock(tinfo->debug_mutex); } while(0); };
#define DEBUG_PRINT_MATRIX(x) if (DEBUG_MODE) {print_matrix(x); };

struct thread_info {
    pthread_t thread_id;

    int start_index, end_index;
    int index;

    sem_t *semMineTop, *semMineBottom;
    sem_t *semOtherTop, *semOtherBottom;

    pthread_mutex_t *debug_mutex;

    MATRIX_DATA *data;
    STENCIL *stencil;
};

void thread_print_matrix(struct thread_info *tinfo, char *info) {
#if DEBUG_MODE
    pthread_mutex_lock(tinfo->debug_mutex);

    DEBUG_LOG("Thread %d: %s\n", tinfo->index, info);
    print_matrix(tinfo->data);
    DEBUG_LOG("-----------------------------\n");

    pthread_mutex_unlock(tinfo->debug_mutex);
#endif
}

void thread_print_matrix_and_vector(struct thread_info *tinfo, INT_MATRIX vector, int vector_size, char *info) {
#if DEBUG_MODE
    pthread_mutex_lock(tinfo->debug_mutex);

    DEBUG_LOG("Thread %d: %s\n", tinfo->index, info);
    print_matrix(tinfo->data);
    DEBUG_LOG("Vector:\n");
    print_vector(vector, vector_size);
    DEBUG_LOG("----------------------------\n");

    pthread_mutex_unlock(tinfo->debug_mutex);
#endif
}


double calculation_start_time;

static pthread_barrier_t barrier;

static void* calculate_submatrix(void *arg){
    struct thread_info *tinfo = arg;

    pthread_barrier_wait(&barrier);
    if (tinfo->index == 0) {
        calculation_start_time = mytime();
    }

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
            memcpy(&last_row[1], &matrix[MATRIX_POSITION(tinfo->start_index - 1, 0, data)], data->column_count * sizeof(int));
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

            if (row < tinfo->end_index - 1) {
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
                THREAD_DEBUG_LOG(tinfo, "CondMineTop Semaphore Post in Thread %d\n", tinfo->index);

                sem_post(tinfo->semMineTop);
            }

            if (row == tinfo->end_index - 1) {
                THREAD_DEBUG_LOG(tinfo, "CondMineBottom Semaphore Post in Thread %d\n", tinfo->index);

                sem_post(tinfo->semMineBottom);
            }
        }

        if (tinfo->semOtherTop != SEM_FAILED) {
            THREAD_DEBUG_LOG(tinfo, "CondOtherBottom Semaphore Wait in Thread %d\n", tinfo->index);

            sem_wait(tinfo->semOtherTop);
        }

        thread_print_matrix(tinfo, "Before copying bottom_row");
        if (tinfo->start_index != tinfo->end_index - 1) {
            memcpy(&data->matrix[MATRIX_POSITION((tinfo->end_index - 1), 0, data)], &bottom_row[0],
                   data->column_count * sizeof(int));

            if (tinfo->semMineBottom != SEM_FAILED) {
                sem_post(tinfo->semMineBottom);
            }
        }

        if (tinfo->semOtherBottom != SEM_FAILED) {
            THREAD_DEBUG_LOG(tinfo, "CondOtherTop Semaphore Wait in Thread %d\n", tinfo->index);

            sem_wait(tinfo->semOtherBottom);
        }
        thread_print_matrix_and_vector(tinfo, bottom_row, data->column_count, "After copying bottom_row, before copying top_row");

        memcpy(&data->matrix[MATRIX_POSITION(tinfo->start_index, 0, data)], &top_row[0], data->column_count * sizeof(int));

        if (tinfo->semMineTop != SEM_FAILED) {
            sem_post(tinfo->semMineTop);
        }

        if (tinfo->start_index == tinfo->end_index - 1 && tinfo->semMineBottom != SEM_FAILED) {
            sem_post(tinfo->semMineBottom);
        }

        thread_print_matrix_and_vector(tinfo, top_row, data->column_count, "After copying top_row");

        if (tinfo->semOtherBottom != SEM_FAILED) {
            sem_wait(tinfo->semOtherBottom);
        }

        if (tinfo->semOtherTop != SEM_FAILED) {
            sem_wait(tinfo->semOtherTop);
        }
    }

    free(last_row);
    free(current_row);
    free(top_row);
    free(bottom_row);

    return NULL;
}

#define SEMAPHORE_NAME "semaphore7_%d"

sem_t *create_semaphore(const char *name) {
    sem_t *result = sem_open(name, O_CREAT | O_EXCL, 0600, 0);
    if (result == SEM_FAILED) {
        DEBUG_LOG("Failed to instantiate Semaphore %s\n", name);
        assert(0);
    }
    return result;
}

void stencil_pthread(MATRIX_DATA *data, STENCIL *stencil, int thread_count) {
    if (thread_count > data->row_count) {
        thread_count = data->row_count;
    }
    calculation_start_time = 0;

    struct thread_info tinfo[thread_count];
    pthread_mutex_t debug_mutex;
    pthread_mutex_init(&debug_mutex, NULL);

    for (int i = 0; i < thread_count; i++) {
        tinfo[i].index = i;
        tinfo[i].start_index = data->row_count/thread_count * i;
        tinfo[i].end_index = data->row_count/thread_count * (i + 1);
        tinfo[i].data = data;
        tinfo[i].stencil = stencil;
        tinfo[i].debug_mutex = &debug_mutex;

        char sem1[20], sem2[20];
        sprintf(&sem1[0], SEMAPHORE_NAME, i * 2);
        sprintf(&sem2[0], SEMAPHORE_NAME, i * 2 + 1);
        sem_unlink(sem1);
        sem_unlink(sem2);

        if (i == 0) {
            tinfo[i].semMineBottom = create_semaphore(sem2);
            tinfo[i].semMineTop = SEM_FAILED;
        } else if (i < thread_count -1) {
            tinfo[i].semMineBottom = create_semaphore(sem2);
            tinfo[i].semMineTop = create_semaphore(sem1);
        } else {
            tinfo[i].semMineTop = create_semaphore(sem1);
            tinfo[i].semMineBottom = SEM_FAILED;
        }
    }

    tinfo[thread_count - 1].end_index = data->row_count;

    if (thread_count > 1) {
        for (int i = 0; i < thread_count; i++) {
            if (i == 0) {
                tinfo[i].semOtherBottom = SEM_FAILED;
                tinfo[i].semOtherTop = tinfo[i + 1].semMineTop;
            } else if (i < thread_count - 1) {
                tinfo[i].semOtherBottom = tinfo[i - 1].semMineBottom;
                tinfo[i].semOtherTop = tinfo[i + 1].semMineTop;
            } else {
                tinfo[i].semOtherTop = SEM_FAILED;
                tinfo[i].semOtherBottom = tinfo[i - 1].semMineBottom;
            }
        }
    } else {
        tinfo[0].semOtherBottom = SEM_FAILED;
        tinfo[0].semOtherTop = SEM_FAILED;
    }

    DEBUG_LOG("Apply stencil on Matrix: \n");
    DEBUG_PRINT_MATRIX(data);

    for (int i = 0; i < thread_count; i++) {
        DEBUG_LOG("Create Instance: Index %d, Start: %d, End: %d\n",
                  tinfo[i].index, tinfo[i].start_index, tinfo[i].end_index);
    }

    pthread_barrier_init(&barrier, NULL, (unsigned int) thread_count);

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&tinfo[i].thread_id, NULL, &calculate_submatrix, &tinfo[i]);
    }

    DEBUG_LOG("\n");

    for (int i = 0; i < thread_count; i++) {
        pthread_join(tinfo[i].thread_id, NULL);
    }

    double elapsed_time = mytime() - calculation_start_time;
    printf("Stopped time for pThread: %.3f ms\n", (float)elapsed_time);


    pthread_barrier_destroy(&barrier);

    for (int i = 0; i < thread_count; i++) {
        sem_close(tinfo[i].semMineBottom);
        sem_close(tinfo[i].semMineTop);

        char sem1[20], sem2[20];
        sprintf(&sem1[0], SEMAPHORE_NAME, i * 2);
        sprintf(&sem2[0], SEMAPHORE_NAME, i * 2 + 1);

        sem_unlink(sem1);
        sem_unlink(sem2);
    }
}