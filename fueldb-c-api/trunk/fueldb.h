//
//  fueldb.c
//  FuelDB-Client
//
//  Created by Joris Basiglio on 10/7/14.
//  Copyright (c) 2014 Wonderfuel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 32
#define WRITE_MSG "{\"type\":\"set\",\"point\":\"%s\",\"value\":\"%s\"}"
#define READ_MSG "{\"type\":\"read\",\"point\":\"%s\"}"
#define BROWSE_MSG "{\"type\":\"browse\",\"point\":\"%s\"}"

int connectFuelDB(const char* address, int port);
int writeToPoint(const char* point, const char* value);
char* readFromPoint(const char* point);
char* browseFromPoint(const char* point);
int closeConnection();
