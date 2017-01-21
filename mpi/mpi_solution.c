//
// Created by Robert Fischer on 14.01.17.
//

#include <string.h>
#include <stdlib.h>
#include "mpi_solution.h"
#include "assert.h"
#include "../definitions/shared.h"
#include <mpi.h>
#include <sys/param.h>
#include "../tests/test_generator.h"
#include "../sequential/sequential_solution.h"
#include "../tests/test_stencil.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int thread_count, thread_num;

    MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_num);

    assert(argc == 5 && "argv must have 5 arguments");

    const char *name = argv[1];
    int iteration_count = (int)strtol(argv[2], NULL, 10);
    int row_count = (int)strtol(argv[3], NULL, 10);
    int column_count = (int)strtol(argv[4], NULL, 10);
    double calculation_start_time = 0;

    thread_count = MIN(row_count, thread_count);

    STENCIL stencil = {
            NULL,
            iteration_count
    };
    MATRIX_DATA *input_data = NULL;
    MATRIX_DATA *input_expected_data = NULL;

    if (strcmp(name, "big_matrix") == 0) {
        stencil.stencil_func = &add_stencil_func;
    } else if (strcmp(name, "constant_matrix") == 0) {
        stencil.stencil_func = &increment_stencil_func;
    } else if (strcmp(name, "simple_matrix") == 0) {
        stencil.stencil_func = &add_stencil_func;
    } else {
        assert(0 && "Unknown Parameter");
    }

    if (thread_num == 0) {
        if (strcmp(name, "big_matrix") == 0) {
            int randomseed = rand();
            srand(randomseed);
            input_data = generate_big_matrix(row_count, column_count);

            srand(randomseed);
            input_expected_data = generate_big_matrix(row_count, column_count);
            check_equal(input_data, input_expected_data);

            stencil_sequential(input_expected_data, &stencil);
        } else if (strcmp(name, "constant_matrix") == 0) {
            input_data = generate_constant_matrix(row_count, column_count);
            input_expected_data = generate_constant_expected_matrix(row_count, column_count, iteration_count);
        } else if (strcmp(name, "simple_matrix") == 0) {
            assert(row_count == 4 && column_count == 4);
            input_data = generate_simple_matrix();
            input_expected_data = generate_simple_expected_matrix();
        } else {
            assert(0 && "Unknown Parameter");
        }

        // send matrix
        INT_MATRIX boundary = malloc(sizeof(int) * (column_count + 2));
        for (int i = 1; i < thread_count; i++) {
            int start_index = row_count / thread_count * i;
            int end_index = row_count / thread_count * (i + 1);

            if (thread_count - 1 == i) {
                end_index = row_count;
            }
            int error_code = MPI_Send(&input_data->matrix[MATRIX_POSITION(start_index, 0, input_data)],
                                      (end_index - start_index) * column_count,
                                      MPI_INT, i, 0, MPI_COMM_WORLD);
            if (error_code != MPI_SUCCESS) {
                char error_string[BUFSIZ];
                int length_of_error_string;

                MPI_Error_string(error_code, error_string, &length_of_error_string);
                printf("%3d: %s\n", thread_num, error_string);
            }

            MPI_Send(&input_expected_data->matrix[MATRIX_POSITION(start_index, 0, input_expected_data)],
                     (end_index - start_index) * column_count,
                     MPI_INT, i, 0, MPI_COMM_WORLD);

            MPI_Send(&input_data->left[start_index], end_index - start_index, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&input_data->right[start_index], end_index - start_index, MPI_INT, i, 0, MPI_COMM_WORLD);

            boundary[0] = input_data->left[start_index - 1];
            memcpy(&boundary[1], &input_data->matrix[MATRIX_POSITION(start_index - 1, 0, input_data)], sizeof(int) * column_count);
            boundary[column_count + 1] = input_data->right[start_index - 1];
            MPI_Send(boundary, column_count + 2, MPI_INT, i, 0, MPI_COMM_WORLD);

            if (i == thread_count - 1) {
                MPI_Send(input_data->bottom, column_count + 2, MPI_INT, i, 0, MPI_COMM_WORLD);
            } else {
                boundary[0] = input_data->left[end_index];
                memcpy(&boundary[1], &input_data->matrix[MATRIX_POSITION(end_index, 0, input_data)], sizeof(int) * column_count);
                boundary[column_count + 1] = input_data->right[end_index];
                MPI_Send(boundary, column_count + 2, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
        failsafe_free((void**)&boundary);
    }
    MATRIX_DATA *data = NULL;
    MATRIX_DATA *expected_data = NULL;
    if (thread_num < row_count) {
        //printf("Current thread num %d of %d\n", thread_num, thread_count);

        int abs_start_index = row_count / thread_count * thread_num;
        int abs_end_index = row_count / thread_count * (thread_num + 1);

        if (thread_count - 1 == thread_num) {
            abs_end_index = row_count;
        }

        int num_of_elements = (abs_end_index - abs_start_index) * column_count;
        int num_of_left_right = abs_end_index - abs_start_index;
        int num_of_top_bottom = column_count + 2;

        INT_MATRIX matrix = malloc(sizeof(int) * num_of_elements);
        INT_MATRIX expected_matrix = malloc(sizeof(int) * num_of_elements);

        BOUNDARY left = NULL;
        BOUNDARY right = NULL;
        BOUNDARY top = NULL;
        BOUNDARY bottom = NULL;

        if (thread_num > 0) {
            MPI_Recv(&matrix[0], num_of_elements, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            /*if (thread_num == 0) {
                printf("Matrix: \n");
                print_vector(matrix, num_of_elements);
            }*/

            MPI_Recv(&expected_matrix[0], num_of_elements, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            /*if (thread_num == 0) {
                printf("Expected Matrix: \n");
                print_vector(expected_matrix, num_of_elements);
            }*/

            left = malloc(sizeof(int) * num_of_left_right);
            MPI_Recv(left, num_of_left_right, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            /*if (thread_num == 0) {
                printf("Left: \n");
                print_vector(left, num_of_left_right);
            }*/

            right = malloc(sizeof(int) * num_of_left_right);
            MPI_Recv(right, num_of_left_right, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            /*if (thread_num == 0) {
                printf("Right: \n");
                print_vector(right, num_of_left_right);
            }*/
            top = malloc(sizeof(int) * num_of_top_bottom);
            MPI_Recv(top, num_of_top_bottom, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            /*if (thread_num == 0) {
                printf("Top: \n");
                print_vector(top, num_of_top_bottom);
            }*/

            bottom = malloc(sizeof(int) * num_of_top_bottom);
            MPI_Recv(bottom, num_of_top_bottom, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            /*if (thread_num == 0) {
                printf("Bottom: \n");
                print_vector(bottom, num_of_top_bottom);
            }*/
        } else {
            //printf("States %d: %p %p %p %p %p\n", thread_num, &input_data->matrix[0], input_expected_data->matrix, input_data->left,
            //       input_data->right, input_data->top, input_data->bottom);
            matrix = input_data->matrix;
            expected_matrix = input_expected_data->matrix;
            left = input_data->left;
            right = input_data->right;
            top = input_data->top;

            if (thread_num == thread_count - 1) {
                bottom = input_data->bottom;
            } else {
                bottom = malloc(sizeof(int) * num_of_top_bottom);

                bottom[0] = input_data->left[abs_end_index];
                memcpy(&bottom[1], &input_data->matrix[MATRIX_POSITION(abs_end_index, 0, input_data)], sizeof(int) * column_count);
                bottom[column_count + 1] = input_data->right[abs_end_index];
            }
        }

        data = malloc(sizeof(MATRIX_DATA));
        data->top = top;
        data->bottom = bottom;
        data->left = left;
        data->right = right;
        data->matrix = matrix;
        data->column_count = column_count;
        data->row_count = abs_end_index - abs_start_index;

        expected_data = malloc(sizeof(MATRIX_DATA));
        expected_data->top = top;
        expected_data->bottom = bottom;
        expected_data->left = left;
        expected_data->right = right;
        expected_data->matrix = expected_matrix;
        expected_data->column_count = column_count;
        expected_data->row_count = abs_end_index - abs_start_index;

        if (thread_num == 0) {
            calculation_start_time = MPI_Wtime();
        }

        INT_MATRIX last_row = malloc(sizeof(int) * (data->column_count + 2));
        INT_MATRIX current_row = malloc(sizeof(int) * (data->column_count + 2));

        for (int iteration = 0; iteration < stencil.iteration_count; iteration++) {
            int values[3][3];
            for (int row = 0; row < 3; row++) {
                for (int column = 0; column < 3; column++) {
                    values[row][column] = get_matrix_value(row, column, data);
                }
            }

            memcpy(last_row, data->top, (data->column_count + 2) * sizeof(int));
            current_row[0] = data->left[0];
            memcpy(&current_row[1], data->matrix, data->column_count * sizeof(int));
            current_row[data->column_count + 1] = data->right[0];


            for (int row = 0; row < data->row_count; row++) {
                for (int column = 0; column < data->column_count; column++) {
                    int value = stencil.stencil_func(values);
                    matrix[MATRIX_POSITION(row, column, data)] = value;


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
                    memcpy(&current_row[1], &data->matrix[MATRIX_POSITION(row + 1, 0, data)],
                           data->column_count * sizeof(int));
                    current_row[data->column_count + 1] = data->right[row + 1];
                }
            }

            //printf("Sending begin\n");
            MPI_Request requests[4];
            MPI_Status statuses[4];
            int count = 0;

            if (thread_num > 0) {
                MPI_Isend(matrix, column_count, MPI_INT, thread_num - 1, 0, MPI_COMM_WORLD, &requests[count]);
                count++;
            }

            if (thread_num + 1 < thread_count) {
                MPI_Isend(&matrix[MATRIX_POSITION(data->row_count - 1, 0, data)], column_count,
                          MPI_INT, thread_num + 1, 0, MPI_COMM_WORLD, &requests[count]);
                count++;
            }
            //printf("Sending done\n");

            if (thread_num > 0) {
                MPI_Irecv(&data->top[1], column_count, MPI_INT, thread_num - 1, 0, MPI_COMM_WORLD, &requests[count]);
                count++;
            }

            if (thread_num + 1 < thread_count) {
                MPI_Irecv(&data->bottom[1], column_count, MPI_INT, thread_num + 1, 0, MPI_COMM_WORLD, &requests[count]);
                count++;
            }
            MPI_Waitall(count, &requests[0], &statuses[0]);
        }

        failsafe_free((void**)&last_row);
        failsafe_free((void**)&current_row);
    }/**/

    MPI_Barrier(MPI_COMM_WORLD);

    if (thread_num == 0) {
        double elapsed_time = MPI_Wtime() - calculation_start_time;
        printf("Stopped time for Open MPI: %.3f ms\n", (float)elapsed_time*1000);
    }

    if (thread_num < row_count) {
        check_equal(data, expected_data);
    }

    free_matrixdata(input_data);
    free_matrixdata(input_expected_data);
    if (thread_num == 0) {
        if (thread_num < thread_count - 1) {
            failsafe_free((void**)&data->bottom); // only bottom has its own malloc, because of reasons
        }
        failsafe_free((void**)&data); // because expected_data is basically a copy of input_data
    } else {
        free_matrixdata(data);
    }

    MPI_Finalize();
}