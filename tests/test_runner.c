//
// Created by Robert Fischer on 05.12.16.
//

#include <stdio.h>
#include <assert.h>
#include <libiomp/omp.h>

#include "../definitions/shared.h"

#include "test_runner.h"

#include "test_cases/test_big_matrix.h"
#include "test_cases/test_simple_matrix.h"
#include "test_cases/test_constant_matrix.h"
#include "test_stencil.h"

double mytime(void);

int main(int argc, char **args) {
    //printf("Benchmark:\n");
    //test_big_matrix(3, 3, 2, 2);

    printf("---------------------------------------\n");
    printf("Test Constant Matrix \n");
    for (int row_count = 1; row_count < 20; row_count++) {
        for (int column_count = 1; column_count < 20; column_count++) {
            printf("... with size row_count: %d column_count: %d\n", row_count, column_count);
            for (int thread_count = 1; thread_count < 20; thread_count++) {
                printf("... with thread_count %d\n", thread_count);
                test_constant_matrix(row_count, column_count, thread_count, 4);
            }
        }
    }

    printf("Success Constant Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Simple Matrix \n");
    test_simple_matrix(5);
    printf("Success Simple Matrix \n");

    printf("---------------------------------------\n");
    printf("Test Big Matrix\n");
    test_big_matrix(500, 500, 8, 20);
    printf("Success Big Matrix\n");

    printf("---------------------------------------\n");
    printf("All tests finished successfully\n");

    return 0;
}

double started_time;
void start_timer() {
    started_time = mytime();
}

void end_timer(const char * msg) {
    printf("Stopped time for %s: %.3f\n", msg, (float)(mytime() - started_time));
    started_time = 0;
}

#include <sys/time.h>
double mytime(void)  {
    struct timeval now; gettimeofday(&now,NULL);
    return (double)((long long)now.tv_usec+
    (long long)now.tv_sec*1000000);
}
