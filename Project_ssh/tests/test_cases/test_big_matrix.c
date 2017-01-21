//
// Created by Robert Fischer on 29.12.16.
//

#include <string.h>
#include <stdlib.h>
#include "../../definitions/shared.h"
#include "../test_runner.h"
#include "../test_generator.h"

void test_big_matrix(int row_count, int column_count, int thread_count, int iteration_count) {
#if RUN_MPI
    printf("Open MPI Implementation \n");
    run_mpi("big_matrix", iteration_count, row_count, column_count, thread_count);
#else
    unsigned int randomseed = (unsigned int) rand();
    srand(randomseed);
    MATRIX_DATA *data1 = generate_big_matrix(row_count, column_count);
    srand(randomseed);
    MATRIX_DATA *data2 = generate_big_matrix(row_count, column_count);
    srand(randomseed);
    MATRIX_DATA *data3 = generate_big_matrix(row_count, column_count);
    srand(randomseed);
    MATRIX_DATA *data4 = generate_big_matrix(row_count, column_count);


    STENCIL stencil = {
            &add_stencil_func,
            iteration_count
    };

    printf("Sequential Implementation \n");
    stencil_sequential(data1, &stencil);

    printf("pThread Implementation \n");
    stencil_pthread(data2, &stencil, thread_count);
    check_equal(data1, data2);

    printf("OpenMP Implementation \n");
    stencil_openmp(data3, &stencil);
    check_equal(data1, data3);

    printf("Cilk Implementation \n");
    stencil_cilk(data4, &stencil, thread_count);
    check_equal(data1, data4);

    free_matrixdata(data1);
    free_matrixdata(data2);
    free_matrixdata(data3);
    free_matrixdata(data4);
#endif
}