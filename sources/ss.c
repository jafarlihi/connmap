#include "ss.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *ssOutput;

void refreshConnections() {
    ssOutput = popen("ss -atun4 | grep ESTAB | awk '{print $6}'", "r");
    if (ssOutput == NULL) {
        printf("Failed to run ss command\n" );
        exit(1);
    }
}

char *getConnection() {
    char ipPort[128];

    while (fgets(ipPort, 128, ssOutput) != NULL) {
        int index = 0;
        while (ipPort[index++] != ':');
        char *ip = malloc(sizeof(char) * index - 1);
        strncpy(ip, ipPort, index - 1);
        return ip;
    }

    pclose(ssOutput);
    return NULL;
}

