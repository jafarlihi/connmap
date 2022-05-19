#ifndef IP_H
#define IP_H

#include <stdint.h>

typedef struct IPRange {
    uint64_t start;
    uint64_t end;
    double latitude;
    double longitude;
} IPRange;

void initIPDatabase();
IPRange getCoordinates(char *ip);

#endif

