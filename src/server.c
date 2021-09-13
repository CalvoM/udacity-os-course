#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include "../include/questions.h"

int spawn_server(char *port){
    int restype;
    struct addrinfo hints,*res;
    struct sockaddr_storage client_addr;

    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((restype = getaddrinfo(NULL,port,&hints,&res)) != 0){
        printf("Could not get the details of the host\n");
        return restype;
    }
    int sockfd = get_socket_from_addr(res);
    if(sockfd == -1){
        printf("Socket could not be created\n");
        return -1;
    }
    int yes=1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) ==-1){
        perror("setsockopt\n");
        return restype;

    }
    if((restype = bind(sockfd,res->ai_addr,res->ai_addrlen)) != 0){
        printf("socket error: %s\n",strerror(errno));
        return restype;
    }
    if((restype = listen(sockfd,20))!= 0){
        printf("%s\n",strerror(errno));
        return restype;
    }
    socklen_t client_addr_sz = sizeof client_addr;
    int client_fd = accept(sockfd,(struct sockaddr *)&client_addr,&client_addr_sz);
    if(client_fd == -1){
        printf("accept error\n");
        return -1;
    }
    printf("Received connection from client\n");
    return close(sockfd);

}