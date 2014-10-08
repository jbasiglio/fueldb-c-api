//
//  fueldb.c
//  FuelDB-Client
//
//  Created by Joris Basiglio on 9/13/14.
//  Copyright (c) 2014 Wonderfuel. All rights reserved.
//
#include "fueldb.h"


int sock = -1;
int status = -1;
struct sockaddr_in server;

int connectFuelDB(const char* address, int port){
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        perror("Could not create socket");
        return -1;
    }
    server.sin_addr.s_addr = inet_addr(address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Connect failed");
        return -1;
    }
    status = 0;
    return 0;
}

int writeToPoint(const char* point, const char* value){
    if(status == -1){
        perror("You have to connect first");
        return -1;
    }
    char* buff=NULL;
    size_t sz;
    sz = snprintf(NULL, 0, WRITE_MSG, point, value);
    buff = malloc(sz + 1);
    snprintf(buff, sz+1, WRITE_MSG, point, value);
    if( write(sock, buff, strlen(buff)) < 0)
    {
        perror("Send failed");
        return -1;
    }
    free(buff);
    buff=NULL;
    buff = malloc(BUFFER_SIZE*sizeof(char));
    size_t len = -1;
    while(len == -1 || buff[len-1] != '\3'){
        len = read(sock, buff, BUFFER_SIZE);
    }
    free(buff);
    buff=NULL;
    return 0;
}

char* sendMsg(const char* point, const char* template){
    if(status == -1){
        perror("You have to connect first");
        return NULL;
    }
    char* buff=NULL;
    size_t sz;
    sz = snprintf(NULL, 0, template, point);
    buff = malloc(sz + 1);
    snprintf(buff, sz+1, template, point);
    if( write(sock, buff, strlen(buff)) < 0)
    {
        perror("Send failed");
        return NULL;
    }
    free(buff);
    buff=NULL;
    char* msg = malloc(sizeof(char));
    buff = malloc(BUFFER_SIZE*sizeof(char));
    size_t len = -1;
    while(len == -1 || buff[len-1] != '\3'){
        memset(buff, 0, BUFFER_SIZE);
        len = read(sock, buff, BUFFER_SIZE);
	   int d = strlen(msg==NULL?"":msg);
        msg = realloc(msg,(d+len)*sizeof(char));
	memcpy(msg+d,buff,len);
    }
    free(buff);
    buff=NULL;
    msg[strlen(msg)-1] = '\0';
    return msg;
}

char* readFromPoint(const char* point){
    return sendMsg(point, READ_MSG);
}

char* browseFromPoint(const char* point){
    return sendMsg(point, BROWSE_MSG);
}

int closeConnection(){
    status=-1;
    return close(sock);
}


