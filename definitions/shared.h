//
// Created by Robert Fischer on 05.12.16.
//

#ifndef PROJECT_SHARED_H
#define PROJECT_SHARED_H


#include "stdio.h"

#define DEBUG_MODE 0

#define DEBUG_LOG(fmt, ...) do { if (DEBUG_MODE) fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)

typedef int* INT_MATRIX;
typedef int* BOUNDARY;

typedef struct {
    INT_MATRIX matrix;
    int column_count;
    int row_count;
    BOUNDARY top;
    BOUNDARY bottom;
    BOUNDARY left;
    BOUNDARY right;
} MATRIX_DATA;

typedef int (*STENCIL_FUNC)(int[3][3]);

typedef struct {
    STENCIL_FUNC stencil_func;
    int iteration_count;
} STENCIL;

#define MATRIX_POSITION(row, column, matrix) ((row) * (matrix->column_count) + (column))

int get_matrix_value(int row, int column, MATRIX_DATA *data);

void print_matrix(MATRIX_DATA *data);
void print_vector(INT_MATRIX data, int vector_size);

#endif //PROJECT_SHARED_H
