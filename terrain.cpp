#include "terrain.h"
#include "climits"

#define GRASS_COST 5

Terrain::Terrain(char cost)
{
    this->cost = cost;
}

char Terrain::getCost()
{
    return cost;
}

Building::Building(): Terrain(CHAR_MAX)
{}

char Building::getChar()
{
    return '#';
}

Grass::Grass(): Terrain(GRASS_COST)
{}

char Grass::getChar()
{
    return ' ';
}
