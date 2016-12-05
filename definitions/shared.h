//
// Created by Robert Fischer on 05.12.16.
//

#ifndef PROJECT_SHARED_H
#define PROJECT_SHARED_H

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

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MATRIX_POSITION(row, column, matrix) ((row) * matrix->column_count + (column))

#endif //PROJECT_SHARED_H
