//
// Created by Robert Fischer on 29.12.16.
//

#include <string.h>
#include "test_constant_matrix.h"

#include "../../definitions/shared.h"
#include "../test_runner.h"
#include "../test_generator.h"

void test_constant_matrix(int row_count, int column_count, int thread_count, int iteration_count) {
#if RUN_MPI
    printf("Open MPI Implementation \n");
    run_mpi("constant_matrix", iteration_count, row_count, column_count, thread_count);
#else
    MATRIX_DATA *data1 = generate_constant_matrix(row_count, column_count);
    MATRIX_DATA *data2 = generate_constant_matrix(row_count, column_count);
    MATRIX_DATA *data3 = generate_constant_matrix(row_count, column_count);
    MATRIX_DATA *data4 = generate_constant_matrix(row_count, column_count);
    MATRIX_DATA *expected_data = generate_constant_expected_matrix(row_count, column_count, iteration_count);

    STENCIL stencil = {
            &increment_stencil_func,
            iteration_count
    };

    printf("Sequential Implementation \n");
    stencil_sequential(data1, &stencil);
    check_equal(data1, expected_data);

    printf("pThread Implementation \n");
    stencil_pthread(data2, &stencil, thread_count);
    check_equal(data2, expected_data);

    printf("OpenMP Implementation \n");
    stencil_openmp(data3, &stencil);
    check_equal(data3, expected_data);

    printf("Cilk Implementation \n");
    stencil_cilk(data4, &stencil, thread_count);
    check_equal(data4, expected_data);

    free_matrixdata(data1);
    free_matrixdata(data2);
    free_matrixdata(data3);
    free_matrixdata(data4);
    free_matrixdata(expected_data);
#endif
}