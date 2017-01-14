//
// Created by Robert Fischer on 05.12.16.
//

#ifndef PROJECT_TEST_RUNNER_H
#define PROJECT_TEST_RUNNER_H

#include "../sequential/sequential_solution.h"
#include "../pthread/pthread_solution.h"
#include "../openmp/openmp_solution.h"
#include "../cilk/cilk_solution.h"
#include "test_stencil.h"

void start_timer();
void end_timer(const char * msg);

#endif //PROJECT_TEST_RUNNER_H
