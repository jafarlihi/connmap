#include "geo.h"
#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

typedef struct CoordinateMapping {
    char *countryCode;
    Coord *coord;
} CoordinateMapping;

CoordinateMapping *map[250];
int mapSize = 0;

void initCoordinateDatabase() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *file = malloc(255);
    for (int i = 0; i < 255; i++)
        file[i] = '\0';

    strcat(file, getenv("HOME"));
    strcat(file, COORDINATESFILE);
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Couldn't open the Coordinates file, exiting\n");
        exit(1);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        CoordinateMapping *coordmap = malloc(sizeof(CoordinateMapping));
        char *countryCode = malloc(3);
        strncpy(countryCode, line, 2);
        countryCode[2] = '\0';
        coordmap->countryCode = countryCode;
        char *lineIterator = line + 3;
        int x = atoi(lineIterator);
        while (*lineIterator != ',')
            lineIterator++;
        lineIterator++;
        int y = atoi(lineIterator);
        Coord *coord = malloc(sizeof(Coord));
        coord->x = x;
        coord->y = y;
        coordmap->coord = coord;
        map[mapSize++] = coordmap;
    }

    fclose(fp);
}

Coord *getCoord(char *countryCode) {
    for (int i = 0; i < mapSize; i++)
        if (strcmp(countryCode, map[i]->countryCode) == 0)
            return map[i]->coord;
}
