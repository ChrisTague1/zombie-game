#include "terrain.h"
#include "climits"

#define GRASS_COST 5

Terrain::Terrain(int cost)
{
    this->cost = cost;
}

int Terrain::getCost()
{
    return cost;
}

Building::Building(): Terrain(INT_MAX)
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
