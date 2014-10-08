//
//  test.c
//  test-app
//
//  Created by Joris Basiglio on 10/7/14.
//  Copyright (c) 2014 Wonderfuel. All rights reserved.
//

#include "../fueldb.h"

int main(int argc , char *argv[])
{
    if(argc < 2){
        printf("You have to specify the IP Adress as first argument\n");
        return -1;
    }
    connectFuelDB(argv[1], 8103);
    writeToPoint("fueldb.iops", "trololo");
    char* buffer = readFromPoint("fueldb.iops");
    printf("Read value: %s\n",buffer);
    free(buffer);
    closeConnection();
    return 0;
}
