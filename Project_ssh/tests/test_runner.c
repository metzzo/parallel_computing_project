//
// Created by Robert Fischer on 05.12.16.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../definitions/shared.h"

#include "test_runner.h"

#include "test_cases/test_big_matrix.h"
#include "test_cases/test_simple_matrix.h"
#include "test_cases/test_constant_matrix.h"
#include "test_stencil.h"

double mytime(void);

int main(int argc, char **args) {
    if (argc != 5) {
        printf("Know your syntax\n");
        return -1;
    }

    int column_count, row_count, thread_count, iteration_count;
    column_count = atoi(args[1]);
    row_count = atoi(args[2]);
    thread_count = atoi(args[3]);
    iteration_count = atoi(args[4]);

    printf("---------------------------------------\n");
    printf("Test Constant Matrix \n");
    test_constant_matrix(row_count, column_count, thread_count, iteration_count);
    printf("Success Constant Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Simple Matrix \n");
    test_simple_matrix(thread_count);
    printf("Success Simple Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Big Matrix\n");
    test_big_matrix(row_count, column_count, thread_count, iteration_count);
    printf("Success Big Matrix\n");

    printf("---------------------------------------\n");
    printf("All tests finished successfully\n");

    return 0;
}

void run_mpi(char *name, int iteration_count, int row_count, int column_count, int thread_count) {
    const char command[1000];
    sprintf(command, "mpirun -np %d /Users/rfischer/Dropbox/Studium_Sem5/PC/Project/mpi/cmake-build-debug/mpi %s %d %d %d", thread_count, name, iteration_count, row_count, column_count);
    int errcode = system(command);
    assert(errcode == 0);
}
