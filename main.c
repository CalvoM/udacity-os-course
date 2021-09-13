#include "include/questions.h"

int main(int argc, char **argv){
    if(argc != 3){
        printf("Usage: <address> <port>");
        return -1;
    }
    client_connect(argv);
}