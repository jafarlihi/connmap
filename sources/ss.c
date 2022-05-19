#include "ss.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *ssOutput;
char ip[16];

void refreshConnections() {
    ssOutput = popen("ss -atun4 | grep ESTAB | awk '{print $6}' | cut -f1 -d\":\"", "r");

    if (ssOutput == NULL) {
        printf("Failed to run ss command\n" );
        exit(1);
    }
}

char *getConnection() {
    while (fgets(ip, 16, ssOutput) != NULL) {
        ip[strcspn(ip, "\n")] = 0;
        if (strlen(ip) < 7) continue;
        return ip;
    }
    pclose(ssOutput);
    return NULL;
}

