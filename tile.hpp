#pragma once

#include "random.hpp"
#include <string>
#include <vector>
#include <queue>

enum tiletype {
	PLAIN,
	RIVER,
	FOREST,
	FOREST_EDGE,
	ROAD,
	NONE
};

struct Tile{
	tiletype type;
};
typedef Tile tile;

int numberOfTileTypes();