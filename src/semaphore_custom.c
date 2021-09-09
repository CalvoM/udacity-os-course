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
    s->is_init = 1;
}
void semaphore_destroy(semaphore_t *s){
    
}
void semaphore_wait(semaphore_t *s){

}
void semaphore_post(semaphore_t *s){

}