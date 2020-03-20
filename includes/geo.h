#ifndef GEO_H
#define GEO_H

typedef struct Coord {
    int x;
    int y;
} Coord;

Coord getCoord(char *countryCode);

#endif

