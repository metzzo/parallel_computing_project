//
// Created by Robert Fischer on 21.01.17.
//

#ifdef __APPLE__

#ifndef PROJECT_PTHREAD_BARRIER_OSX_H
#define PROJECT_PTHREAD_BARRIER_OSX_H

#include <pthread.h>
#include <errno.h>

typedef int pthread_barrierattr_t;
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} pthread_barrier_t;


int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count);

int pthread_barrier_destroy(pthread_barrier_t *barrier);

int pthread_barrier_wait(pthread_barrier_t *barrier);



#endif //PROJECT_PTHREAD_BARRIER_OSX_H

#endif
