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

int main(int argc, char **args) {
    printf("---------------------------------------\n");
    printf("Test Constant Matrix \n");
    /*for (int row_count = 1; row_count < 20; row_count++) {
        for (int column_count = 1; column_count < 20; column_count++) {
            //printf("... with size row_count: %d column_count: %d\n", row_count, column_count);
            for (int thread_count = 1; thread_count < 20; thread_count++) {
                //printf("... with thread_count %d\n", thread_count);
                test_constant_matrix(row_count, column_count, thread_count, 4);
            }
        }
    }*/

    printf("Success Constant Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Simple Matrix \n");
    test_simple_matrix(4);
    printf("Success Simple Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Big Matrix\n");
    test_big_matrix(5000, 5000, 8, 20);
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
