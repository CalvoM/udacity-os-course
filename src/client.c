#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "../include/questions.h"

int client_connect(char **options){
    char *address = options[1];
    char *port = options[2];
    printf("Host: \"%s\", Port:\"%s\"",address,port);
    int restype;
    struct addrinfo hints, *res;
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((restype = getaddrinfo(address,port,&hints,&res))!= 0){
        printf("Could not get the details of the host\n");
        return restype;
    }
    int sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if(sockfd == -1){
        printf("Socket could not be created\n");
        return -1;
    }
    restype = connect(sockfd,res->ai_addr,res->ai_addrlen);
    if(restype != 0 ){
        printf("Could not connect to \"%s:%s\"",address,port);
        return restype;
    }
    close(sockfd);
    return restype;
}