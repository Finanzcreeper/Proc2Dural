#pragma once

#include "random.hpp"
#include <string>
#include <vector>
#include <queue>

enum tiletype {
	NONE,
	PLAIN,
	RIVER,
	FOREST,
	ROAD,
};

enum direction {
	up,
	down,
	left,
	right
};

class tile {
private:
	std::vector<tile> possible_connections;
	std::mt19937 rng;
	
public:
	bool seen = false;
	void fill_directions();
	void add_to_queue(std::queue<tile*> *queue);
	void connect(tile* a, direction dir);
	tile* left;
	tile* up;
	tile* right;
	tile* down;
	std::vector<tile*> directions {up, down, left, right};
	tiletype name;
	void generate_connections();
	tile();
	~tile();
};

void fill_tileset(std::vector<tiletype> &tileset);
void link_tiles(tile _tile);
void plain_rules(tile _tile);
void river_rules(tile _tile);
void forest_rules(tile _tile);
void road_rules(tile _tile);