#include "../include/questions.h"
int done=0;

void *get_roots(void *args){
    int *l = (int *)args;
    double *roots = (double *) malloc(*l);
    int i =0;
    while (i<(*l)){
        roots[i] = sqrt((i));
        i++;
    }
    done = 1;
    return roots; 
}

void counter_threaded(){
    int limit = 101;
    pthread_t t;
    pthread_create(&t,NULL,get_roots,&limit);
    void *ret_val;
    while (done == 0){
        printf("waiting\r\n");
    }
    pthread_join(t,&ret_val);
    double *roots = (double *)ret_val;
    int i =0;
    while(i<limit){
        printf("%.3lf\n",i,roots[i]);
        fflush(stdout);
        i++;
    }
    free(ret_val);
}