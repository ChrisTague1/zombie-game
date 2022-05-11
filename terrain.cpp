#include "terrain.h"
#include "climits"

#define GRASS_COST 5
#define TILE_COST 3
#define TREE_COST 7

Terrain::Terrain(int cost, char c): Cell(c), cost(cost) {}

int Terrain::getCost()
{ return cost; }

Building::Building(): Terrain(INT_MAX, '#') {}

Grass::Grass(): Terrain(GRASS_COST, ' ') {}

Tile::Tile(): Terrain(TILE_COST, '.') {}

Tree::Tree(): Terrain(TREE_COST, '^') {}
