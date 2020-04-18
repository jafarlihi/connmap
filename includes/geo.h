#ifndef GEO_H
#define GEO_H

typedef struct Coord {
    int x;
    int y;
} Coord;

void initCoordinateDatabase();
Coord *getCoord(char *countryCode);

#endif

