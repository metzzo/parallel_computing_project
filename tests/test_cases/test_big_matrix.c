//
// Created by Robert Fischer on 29.12.16.
//

#include <string.h>
#include <stdlib.h>
#include "../../definitions/shared.h"
#include "../test_runner.h"
#include "../test_generator.h"

void test_big_matrix(int row_count, int column_count, int thread_count, int iteration_count) {
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
    start_timer();
    stencil_sequential(data1, &stencil);
    end_timer("Sequential");

    printf("pThread Implementation \n");
    start_timer();
    stencil_pthread(data2, &stencil, thread_count);
    end_timer("pThread");
    check_equal(data1, data2);

    printf("OpenMP Implementation \n");
    start_timer();
    stencil_openmp(data3, &stencil);
    end_timer("OpenMP");
    check_equal(data1, data3);

    printf("Cilk Implementation \n");
    start_timer();
    stencil_cilk(data4, &stencil, thread_count);
    end_timer("Cilk");
    check_equal(data1, data4);

    free_matrixdata(data1);
    free_matrixdata(data2);
    free_matrixdata(data3);
    free_matrixdata(data4);
}