#pragma once

#include "random.hpp"
#include <string>
#include <vector>
#include <queue>

enum tiletype {
	PLAIN,
	RIVER,
	FOREST,
	ROAD,
	NONE
};

struct Tile{
	tiletype type;
};
typedef Tile tile;

int numberOfTileTypes();