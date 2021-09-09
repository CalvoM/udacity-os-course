#ifndef SEMAPHORE_CUSTOM_H
#define SEMAPHORE_CUSTOM_H
#include <pthread.h>

typedef enum{
    uninitialized,
    initialized
}init_t;

typedef struct semaphore{
    int count;
    pthread_mutex_t locker;
    pthread_cond_t is_okay;
    init_t is_init;
    
}semaphore_t;

void semaphore_init(semaphore_t *s,int init_count);
void semaphore_destroy(semaphore_t *s);
void semaphore_wait(semaphore_t *s);
void semaphore_post(semaphore_t *s);
#endif