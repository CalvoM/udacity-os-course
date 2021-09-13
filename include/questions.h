#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define debug(...) \
    printf("[%s] ",__func__); \
    printf(__VA_ARGS__)
void priority_readers_writers_threaded();
void counter_threaded();
int client_connect(char **options);
int spawn_server(char *port);

static int get_socket_from_addr(struct addrinfo *addr){
    return socket(addr->ai_family,addr->ai_socktype,addr->ai_protocol);
}

#endif