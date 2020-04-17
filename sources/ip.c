#include "ip.h"
#include "config.h"

#include <stdlib.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

typedef struct IPRange {
    uint64_t start;
    uint64_t end;
    char *countryCode;
} IPRange;

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

IPRange binarySearch(int l, int r, uint64_t ipnumber) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        IPRange midRange = IPRangeVector_get(vector, mid);
        if (midRange.start <= ipnumber && midRange.end >= ipnumber)
            return midRange;
        if (midRange.start > ipnumber)
            return binarySearch(l, mid - 1, ipnumber);
        return binarySearch(mid + 1, r, ipnumber);
    }
    return (IPRange) {.start = 0, .end = 0, .countryCode = NULL};
}

IPRange getNumberRange(uint64_t ipnumber) {
    return binarySearch(0, vector->size, ipnumber);
}

uint64_t ipToNumber(char *ipstring) {
    uint64_t ip = inet_addr(ipstring);
    uint8_t *ptr = (uint8_t *) &ip;
    uint64_t number = 0;

    if (ipstring != NULL) {
        number =  (uint8_t)(ptr[3]);
        number += (uint8_t)(ptr[2]) * 256;
        number += (uint8_t)(ptr[1]) * 256 * 256;
        number += (uint8_t)(ptr[0]) * 256 * 256 * 256;
    }
    return number;
}

char *getCountryCode(char *ip) {
    uint64_t ipnumber = ipToNumber(ip);
    return getNumberRange(ipnumber).countryCode;
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

    fp = fopen(strcat(getenv("HOME"), IPDBFILE), "r");
    if (fp == NULL) {
        printf("Couldn't open the IPDB file, exiting\n");
        exit(1);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        uint64_t startRange = strtoull(line + 1, NULL, 10);
        char *lineIterator = line + 1;
        while (*lineIterator != '"')
            lineIterator++;
        lineIterator++;
        while (*lineIterator != '"')
            lineIterator++;
        lineIterator++;
        uint64_t endRange = strtoull(line + (lineIterator - line), NULL, 10);
        while (*lineIterator != '"')
            lineIterator++;
        lineIterator++;
        while (*lineIterator != '"')
            lineIterator++;
        lineIterator++;
        char *countryCode = malloc(3);
        strncpy(countryCode, line + (lineIterator - line), 2);
        countryCode[2] = '\0';
        if (strcmp(countryCode, "-\"") == 0)
            continue;
        IPRangeVector_append(vector, (IPRange){.start = startRange, .end = endRange, .countryCode = countryCode});
    }

    fclose(fp);
}
