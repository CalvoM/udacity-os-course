#include "../include/questions.h"
#define WRITERS_NUM 5
#define READERS_NUM 5

int resource = 0;
pthread_mutex_t rwlock;
pthread_cond_t read_ok;
pthread_cond_t writer_done;

void *update_resource(void *args){
    int **rw = (int **)args;
    int *readers = rw[0];
    int *writers = rw[1];
    if(pthread_mutex_lock(&rwlock) != 0){
        printf("MUTEX LOCK ERROR IN WRITER\n");
        return NULL;
    }
    while(*readers > 0){
        pthread_cond_wait(&read_ok,&rwlock);
    }
    resource++;
    (*writers)--;
    printf("[WRITERS] New value = %d and readers = %d\r\n",resource,*readers);
    if(*writers == 0)pthread_cond_signal(&writer_done);
    pthread_mutex_unlock(&rwlock);
    
}

void *get_resource(void *args){
    int *readers = (int *)args;
    if(pthread_mutex_lock(&rwlock) != 0){
        printf("MUTEX LOCK ERROR IN READER\n");
        return NULL;
    }
    printf("[READERS] Value = %d and readers = %d\r\n",resource,*readers);
    (*readers)--;
    if(*readers == 0)pthread_cond_broadcast(&read_ok);
    pthread_mutex_unlock(&rwlock);
    
}

void priority_readers_writers_threaded(){
    pthread_t writers[WRITERS_NUM];
    pthread_t readers[READERS_NUM];
    pthread_mutex_init(&rwlock,NULL);
    pthread_cond_init(&read_ok,NULL);
    int readersN=READERS_NUM,writersN=WRITERS_NUM;
    int ** w_args = (int **)malloc(2);
    w_args[0] = &readersN;
    w_args[1] = &writersN;
    for(int w=0;w<WRITERS_NUM;w++){
        pthread_create(&writers[w],NULL,update_resource,(void *)w_args);
    }
    for(int w=0;w<READERS_NUM;w++){
        pthread_create(&readers[w],NULL,get_resource,&readersN);
    }
    if(pthread_mutex_lock(&rwlock) != 0){
        printf("MUTEX LOCK ERROR IN MAIN\n");
        return;
    }
    while(writersN>0){
        pthread_cond_wait(&writer_done,&rwlock);
    }
    pthread_mutex_unlock(&rwlock);
    for(int w=0;w<WRITERS_NUM;w++){
        pthread_join(writers[w],NULL);
    }
    for(int w=0;w<READERS_NUM;w++){
        pthread_join(readers[w],NULL);
    }
    pthread_mutex_destroy(&rwlock);
    pthread_cond_destroy(&read_ok);

}