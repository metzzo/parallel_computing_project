//
// Created by Robert Fischer on 14.01.17.
//


#include <stdlib.h>
#include <string.h>
#include "test_generator.h"
#include "../definitions/shared.h"

MATRIX_DATA* init_matrix(int row_count, int column_count) {
    int *input_matrix = malloc(sizeof(int) * row_count * column_count);

    int *boundaries_bottom = malloc(sizeof(int) * (column_count + 2));
    int *boundaries_top = malloc(sizeof(int) * (column_count + 2));
    int *boundaries_right = malloc(sizeof(int) * row_count);
    int *boundaries_left = malloc(sizeof(int) * row_count);

    for (int column = 0; column < column_count + 2; column++) {
        boundaries_bottom[column] = boundaries_top[column] = 1;
    }
    for (int row = 0; row < row_count; row++) {
        boundaries_left[row] = boundaries_right[row] = 1;
    }

    MATRIX_DATA *data = malloc(1 * sizeof(MATRIX_DATA));
    data->matrix = input_matrix;
    data->column_count = column_count;
    data->row_count = row_count;
    data->top = boundaries_top;
    data->bottom = boundaries_bottom;
    data->left = boundaries_left;
    data->right = boundaries_right;

    return data;
}

MATRIX_DATA* generate_big_matrix(int row_count, int column_count) {
    MATRIX_DATA *data = init_matrix(row_count, column_count);
    for (int row = 0; row < row_count; row++) {
        for (int column = 0; column < column_count; column++) {
            data->matrix[row * column_count + column] = rand() % 100;
        }
    }
    return data;
}

MATRIX_DATA* generate_constant_matrix(int row_count, int column_count) {
    MATRIX_DATA *data = init_matrix(row_count, column_count);
    for (int row = 0; row < row_count; row++) {
        for (int column = 0; column < column_count; column++) {
            data->matrix[row * column_count + column] = 1;
        }
    }
    return data;
}

MATRIX_DATA* generate_constant_expected_matrix(int row_count, int column_count, int iteration_count) {
    MATRIX_DATA *data = init_matrix(row_count, column_count);
    for (int row = 0; row < row_count; row++) {
        for (int column = 0; column < column_count; column++) {
            data->matrix[row * column_count + column] = 1 + iteration_count;
        }
    }
    return data;
}

MATRIX_DATA* generate_simple_matrix() {
    MATRIX_DATA *data = init_matrix(4, 4);

    int input_matrix[] = {
        1,2,3,4,
        2,3,4,5,
        3,4,5,6,
        4,5,6,7
    };
    BOUNDARY boundaries_top_bottom = (int[6]) {1,2,3,4,5,6};
    BOUNDARY boundaries_left_right = (int[4]) {5,6,7,8};

    memcpy(data->matrix, input_matrix, sizeof(int) * 4*4);

    memcpy(data->bottom, boundaries_top_bottom, sizeof(int) * 6);
    memcpy(data->top, boundaries_top_bottom, sizeof(int) * 6);
    memcpy(data->left, boundaries_left_right, sizeof(int) * 4);
    memcpy(data->right, boundaries_left_right, sizeof(int) * 4);


    return data;
}

MATRIX_DATA* generate_simple_expected_matrix() {
    MATRIX_DATA *data = init_matrix(4, 4);

    int input_matrix[] = {
        25, 24, 33, 42,
        33, 27, 36, 45,
        42, 36, 45, 54,
        37, 36, 45, 54
    };
    BOUNDARY boundaries_top_bottom = (int[6]) {1,2,3,4,5,6};
    BOUNDARY boundaries_left_right = (int[4]) {5,6,7,8};

    memcpy(data->matrix, input_matrix, sizeof(int) * 4*4);

    memcpy(data->bottom, boundaries_top_bottom, sizeof(int) * 6);
    memcpy(data->top, boundaries_top_bottom, sizeof(int) * 6);
    memcpy(data->left, boundaries_left_right, sizeof(int) * 4);
    memcpy(data->right, boundaries_left_right, sizeof(int) * 4);


    return data;
}