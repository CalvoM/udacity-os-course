#include "include/questions.h"

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage: os_programming command <options>...");
        return -1;
    }
    char *cmd = argv[1];
    if(strncmp(cmd,"client",5) == 0){
        if(argc != 5){
            printf("Usage: os_programming client <addr> <port> <msg>");
            return -1;
        }
        client_connect(argv);
    }else if(strncmp(cmd,"server",6)==0){
        if(argc !=3){
            printf("Usage: os_programming server <port>");
            return -1;
        }
        spawn_server(argv[2]);
    }
    return 0;
}