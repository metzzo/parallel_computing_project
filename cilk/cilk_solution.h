//
// Created by Robert Fischer on 31.12.16.
//

#ifndef PROJECT_CILK_SOLUTION_H
#define PROJECT_CILK_SOLUTION_H

#include "../definitions/shared.h"

double stencil_cilk(MATRIX_DATA *data, STENCIL *stencil, int thread_count);

#endif //PROJECT_CILK_SOLUTION_H
