//
// Created by Robert Fischer on 28.01.17.
//

#include <assert.h>
#include <stdlib.h>
#include <printf.h>
#include <string.h>
#include "benchmark_runner.h"
#include "../definitions/shared.h"
#include "test_generator.h"
#include "test_stencil.h"
#include "../sequential/sequential_solution.h"
#include "../pthread/pthread_solution.h"
#include "../openmp/openmp_solution.h"
#include "../cilk/cilk_solution.h"

int main(int argc, char **args) {
    if (argc != 7) {
        printf("Know your syntax\n");
        return -1;
    }

    int column_count, row_count, thread_count, iteration_count, stencil_func;
    char *type = args[1];
    column_count = atoi(args[2]);
    row_count = atoi(args[3]);
    thread_count = atoi(args[4]);
    iteration_count = atoi(args[5]);
    stencil_func = atoi(args[6]);

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

    printf("%s, %d, %d, %d, %d, %d, ", type, column_count, row_count, thread_count, iteration_count, stencil_func);

    // sequential
    double times = 0, max_time = 0, min_time = 0;
    for (int i = 0; i < REPRODUCE_COUNT; i++) {
        srand(randomseed);
        MATRIX_DATA *data = generate_big_matrix(row_count, column_count);

        double time = 0;
        if (strcmp(type, "sequential") == 0) {
             time = stencil_sequential(data, &stencil);
        } else if (strcmp(type, "pthread") == 0) {
            time = stencil_pthread(data, &stencil, thread_count);
        } else if (strcmp(type, "openmp") == 0) {
            time = stencil_openmp(data, &stencil);
        } else if (strcmp(type, "cilk") == 0) {
            time = stencil_cilk(data, &stencil, thread_count);
        } else {
            assert(0);
        }

        times += time;
        if (i == 0) {
            max_time = time;
            min_time = time;
        } else if (max_time < time) {
            max_time = time;
        } else if (min_time > time) {
            min_time = time;
        }

        free_matrixdata(data);
    }
    printf("%.3f, %f, %f\n", (float)(times / (double)REPRODUCE_COUNT), (float)max_time, (float)min_time);

    return 0;
}