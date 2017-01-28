//
// Created by Robert Fischer on 05.12.16.
//

#ifndef PROJECT_PTHREAD_H
#define PROJECT_PTHREAD_H

#include "../definitions/shared.h"

double stencil_pthread(MATRIX_DATA *data, STENCIL *stencil, int thread_count);

#endif //PROJECT_PTHREAD_H
