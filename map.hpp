
#ifndef MAP_H
# define MAP_H

#include <string>
#include <vector>
#include <queue>
#include "tile.hpp"

class Map {
	private:
		std::vector<std::vector<tile *>> map;
		int width = 3;
		int height = 3;
		std::vector<tile*> create_tile_creation_order();
		void add_tile(std::vector<tile*> creation_order, tile* aTile);

	public:

		Map(int width, int height);
		~Map();
		void discover_tile_types();
		void print_map();

};




#endif