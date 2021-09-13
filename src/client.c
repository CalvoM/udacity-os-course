#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include "../include/questions.h"

int client_connect(char **options){
    char *address = options[2];
    char *port = options[3];
    char *msg = options[4];
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
    if(send(sockfd,msg,strlen(msg),0) == -1){
        printf("%s\n",strerror(errno));
        return restype;
    }
    printf("Message sent\r\n");
    char buf[strlen(msg)+1];
    if(recv(sockfd,buf,sizeof buf,0) == -1){
        printf("Error receiving from server\n");
        return -1;
    }
    printf("FROM SERVER: %s\n",buf);
    return close(sockfd);
}