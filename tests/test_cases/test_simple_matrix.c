//
// Created by Robert Fischer on 29.12.16.
//

#include "../../definitions/shared.h"
#include "../test_runner.h"
#include "../test_generator.h"


void test_simple_matrix(int thread_count) {
    MATRIX_DATA *data1 = generate_simple_matrix();
    MATRIX_DATA *data2 = generate_simple_matrix();
    MATRIX_DATA *data3 = generate_simple_matrix();
    MATRIX_DATA *data4 = generate_simple_matrix();
    MATRIX_DATA *expected_data = generate_simple_expected_matrix();

    STENCIL stencils = {
            &add_stencil_func,
            1
    };

    printf("Sequential Implementation\n");
    stencil_sequential(data1, &stencils);
    check_equal(data1, expected_data);

    printf("pThread Implementation\n");
    stencil_pthread(data2, &stencils, thread_count);
    check_equal(data2, expected_data);

    printf("OpenMP Implementation \n");
    stencil_openmp(data3, &stencils);
    check_equal(data3, expected_data);

    printf("Cilk Implementation \n");
    stencil_cilk(data4, &stencils, thread_count);
    check_equal(data4, expected_data);


    run_mpi("simple_matrix", 1, 4, 4, thread_count);

    free_matrixdata(data1);
    free_matrixdata(data2);
    free_matrixdata(data3);
    free_matrixdata(data4);
    free_matrixdata(expected_data);
}