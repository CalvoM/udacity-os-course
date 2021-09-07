#include "../include/questions.h"
#define WRITERS_NUM 5
#define READERS_NUM 5

int resource = 0;
pthread_mutex_t wlock;
pthread_mutex_t rlock;

void *update_resource(void *args){
    pthread_mutex_lock(&wlock);
    resource++;
    printf("Updated resource to %d\n",resource);
    pthread_mutex_unlock(&wlock);
}

void *get_resource(void *args){
    printf("Resource = %d\n",resource);

}

void priority_readers_writers_threaded(){
    pthread_t writers[WRITERS_NUM];
    pthread_t readers[READERS_NUM];
    for(int w=0;w<WRITERS_NUM;w++){
        pthread_create(&writers[w],NULL,update_resource,NULL);
    }
    for(int w=0;w<READERS_NUM;w++){
        pthread_create(&readers[w],NULL,get_resource,NULL);
    }
    for(int w=0;w<WRITERS_NUM;w++){
        pthread_join(writers[w],NULL);
    }
    for(int w=0;w<READERS_NUM;w++){
        pthread_join(readers[w],NULL);
    }

}