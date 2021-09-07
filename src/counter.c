#include "../include/questions.h"
int done=0;

pthread_cond_t is_done;
pthread_mutex_t done_mutex;
void *get_roots(void *args){
    int *l = (int *)args;
    double *roots = (double *) malloc(*l);
    int i =0;
    while (i<(*l)){
        roots[i] = sqrt((i));
        i++;
        if(pthread_mutex_lock(&done_mutex) != 0) printf("mutex lock error");
        done = i;
        pthread_mutex_unlock(&done_mutex);
        usleep(10000);
    }
    pthread_cond_signal(&is_done);
    return roots; 
}

void counter_threaded(){
    int limit = 101;
    pthread_t t;
    pthread_cond_init(&is_done,NULL);
    pthread_mutex_init(&done_mutex,NULL);
    pthread_create(&t,NULL,get_roots,&limit);
    void *ret_val;
    if(pthread_mutex_lock(&done_mutex) != 0) printf("main mutex lock error");
    printf("main mutex open\r\n");
    while (done != limit){
        printf("waiting\r\n");
        pthread_cond_wait(&is_done,&done_mutex);
    }
    pthread_mutex_unlock(&done_mutex);
    pthread_join(t,&ret_val);
    double *roots = (double *)ret_val;
    int i =0;
    while(i<limit){
        printf("%.3lf\n",i,roots[i]);
        fflush(stdout);
        i++;
    }
    free(ret_val);
    pthread_cond_destroy(&is_done);
    pthread_mutex_destroy(&done_mutex);
}