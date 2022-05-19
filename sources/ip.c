#include "ip.h"
#include "config.h"

#include <stdlib.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

typedef struct IPRangeVector {
    int size;
    int capacity;
    IPRange *data;
} IPRangeVector;

IPRangeVector *vector;

void IPRangeVector_init(IPRangeVector *vector) {
    vector->size = 0;
    vector->capacity = 128;
    vector->data = malloc(sizeof(IPRange) * vector->capacity);
}

IPRange IPRangeVector_get(IPRangeVector *vector, int index) {
    return vector->data[index];
}

void IPRangeVector_resize(IPRangeVector *vector) {
    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, sizeof(IPRange) * vector->capacity);
    }
}

void IPRangeVector_append(IPRangeVector *vector, IPRange value) {
    IPRangeVector_resize(vector);
    vector->data[vector->size++] = value;
}

IPRange binarySearch(int l, int r, uint64_t ip) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        IPRange midRange = IPRangeVector_get(vector, mid);
        if (midRange.start <= ip && midRange.end >= ip)
            return midRange;
        if (midRange.start > ip)
            return binarySearch(l, mid - 1, ip);
        return binarySearch(mid + 1, r, ip);
    }
    return (IPRange) {.start = 0, .end = 0, .latitude = 0.0, .longitude = 0.0};
}

IPRange getNumberRange(uint64_t ip) {
    return binarySearch(0, vector->size, ip);
}

uint64_t ipToDecimal(char *ip) {
    char *endp;

    unsigned long a = strtoul(ip, &endp, 10);
    if (*endp != '.') return -1;
    unsigned long b = strtoul(ip = endp+1, &endp, 10);
    if (*endp != '.') return -1;
    unsigned long c = strtoul(ip = endp+1, &endp, 10);
    if (*endp != '.') return -1;
    unsigned long d = strtoul(ip = endp+1, &endp, 10);
    if (*endp) return -1;

    return (uint32_t) ((a << 24) | (b << 16) | (c << 8) | d);
}

IPRange getCoordinates(char *ip) {
    uint64_t ipDecimal = ipToDecimal(ip);
    return getNumberRange(ipDecimal);
}

void populateVector(IPRangeVector *vector);

void initIPDatabase() {
    vector = malloc(sizeof(IPRangeVector));
    IPRangeVector_init(vector);
    populateVector(vector);
}

void populateVector(IPRangeVector *vector) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *file = malloc(255);
    for (int i = 0; i < 255; i++)
        file[i] = '\0';

    strcat(file, getenv("HOME"));
    strcat(file, IPV4FILE);
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Couldn't open the IPV4FILE file, exiting\n");
        exit(1);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        uint64_t startRange = strtoull(line, NULL, 10);
        char *lineIterator = line;
        while (*lineIterator != ',')
            lineIterator++;
        lineIterator++;
        uint64_t endRange = strtoull(line + (lineIterator - line), NULL, 10);
        while (*lineIterator != ',')
            lineIterator++;
        lineIterator++;
        double latitude = strtod(line + (lineIterator - line), NULL);
        while (*lineIterator != ',')
            lineIterator++;
        lineIterator++;
        double longitude = strtod(line + (lineIterator - line), NULL);
        IPRangeVector_append(vector, (IPRange){.start = startRange, .end = endRange, .latitude = latitude, .longitude = longitude});
    }

    fclose(fp);
}
