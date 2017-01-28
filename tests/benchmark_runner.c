//
// Created by Robert Fischer on 28.01.17.
//

#include <assert.h>
#include <stdlib.h>
#include <printf.h>
#include "benchmark_runner.h"
#include "../definitions/shared.h"
#include "test_generator.h"
#include "test_stencil.h"
#include "../sequential/sequential_solution.h"
#include "../pthread/pthread_solution.h"
#include "../openmp/openmp_solution.h"
#include "../cilk/cilk_solution.h"

int main(int argc, char **args) {
    if (argc != 6) {
        printf("Know your syntax\n");
        return -1;
    }

    int column_count, row_count, thread_count, iteration_count, stencil_func;
    column_count = atoi(args[1]);
    row_count = atoi(args[2]);
    thread_count = atoi(args[3]);
    iteration_count = atoi(args[4]);
    stencil_func = atoi(args[5]);

    assert(stencil_func == 1 || stencil_func == 2);
    assert(column_count > 0);
    assert(row_count > 0);
    assert(thread_count > 0);
    assert(iteration_count > 0);

    STENCIL stencil = {
            stencil_func == 1 ? &add_stencil_func : &add_stencil_complicated_func,
            iteration_count
    };

    unsigned int randomseed = (unsigned int) (column_count + row_count * 1000 + thread_count * 10000 + iteration_count * 1000000);

    printf("%d, %d, %d, %d, %d, ", column_count, row_count, thread_count, iteration_count, stencil_func);

    // sequential
    for (int i = 0; i < REPRODUCE_COUNT; i++) {
        srand(randomseed);
        MATRIX_DATA *data = generate_big_matrix(row_count, column_count);

        stencil_sequential(data, &stencil);
        printf(", ");
    }

    // pthread
    for (int i = 0; i < REPRODUCE_COUNT; i++) {
        srand(randomseed);
        MATRIX_DATA *data = generate_big_matrix(row_count, column_count);

        stencil_pthread(data, &stencil, thread_count);
        printf(", ");
    }

    // openmp
    for (int i = 0; i < REPRODUCE_COUNT; i++) {
        srand(randomseed);
        MATRIX_DATA *data = generate_big_matrix(row_count, column_count);

        stencil_openmp(data, &stencil);
        printf(", ");
    }

    // cilk
    for (int i = 0; i < REPRODUCE_COUNT; i++) {
        srand(randomseed);
        MATRIX_DATA *data = generate_big_matrix(row_count, column_count);

        stencil_cilk(data, &stencil, thread_count);
        printf(", ");
    }
    printf("\n");

    return 0;
}