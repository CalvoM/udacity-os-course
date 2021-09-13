#include "include/questions.h"

int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: <port>");
        return -1;
    }
    char *port = argv[1];
    spawn_server(port);
}