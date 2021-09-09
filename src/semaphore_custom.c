#include "../include/semaphore_custom.h"


void semaphore_init(semaphore_t *s,int init_count){
    if(s == NULL){
        printf("semaphore cannot be NULL\n");
        return;
    }
    if(s->is_init == 1){
        printf("semaphore already initialized\n");
        return;
    }
    s->count = init_count;
    s->limit = init_count;
    s->is_init = 1;
    pthread_mutex_init(&(s->locker),NULL);
    pthread_cond_init(&(s->is_okay),NULL);
}
void semaphore_destroy(semaphore_t *s){
    if(pthread_mutex_lock(&(s->locker)!=0))printf("Mutex lock not okay\n");return;
    if(s == NULL){
        printf("semaphore cannot be NULL\n");
        pthread_mutex_unlock(&(s->locker));
        return;
    }
    if(s->is_init == 0){
        printf("semaphore not initialized\n");
        pthread_mutex_unlock(&(s->locker));
        return;
    }
    pthread_mutex_destroy(&(s->locker));
    pthread_cond_destroy(&(s->is_okay));
    s->is_init = 0;
    s = NULL;

}
void semaphore_post(semaphore_t *s){
    if(pthread_mutex_lock(&(s->locker)!=0))printf("Mutex lock not okay\n");return;
    if(s == NULL){
        printf("semaphore cannot be NULL\n");
        pthread_mutex_unlock(&(s->locker));
        return;
    }
    if(s->is_init == 0){
        printf("semaphore not initialized\n");
        pthread_mutex_unlock(&(s->locker));
        return;
    }
    if(s->count == s->limit){
        printf("overflow\n");
        pthread_mutex_unlock(&(s->locker));
        return;
    }
    s->count++;
    pthread_cond_signal(&(s->is_okay));
    pthread_mutex_unlock(&(s->locker));
}
void semaphore_wait(semaphore_t *s){
    if(pthread_mutex_lock(&(s->locker)!=0))printf("Mutex lock not okay\n");return;
    if(s == NULL){
        printf("semaphore cannot be NULL\n");
        pthread_mutex_unlock(&(s->locker));
        return;
    }
    if(s->is_init == 0){
        printf("semaphore not initialized\n");
        pthread_mutex_unlock(&(s->locker));
        return;
    }
    while(s->count == 0){
        pthread_cond_wait(&(s->is_okay),&(s->locker));
    }
    s->count--;
    pthread_mutex_unlock(&(s->locker));
}