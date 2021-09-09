#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <semaphore.h>

#define debug(...) \
    printf("[%s] ",__func__); \
    printf(__VA_ARGS__)
void priority_readers_writers_threaded();
void counter_threaded();

#endif