
#ifndef MAP_H
# define MAP_H

	#include <string>
	#include <vector>
	#include <queue>
	#include <stdexcept>
	#include "tile.hpp"
	#include "connection_rules.hpp"


	class Map {
		private:
			std::vector<std::vector<tile>> map;
			bool inBounds(int x, int y);
			void addValidNeighbour(int x, int y, std::vector<tile*> &neighbours);

		public:
			int width = 3; // x-value
			int height = 3; // y-value
			std::vector<tile*> getNeighbours(int x, int y);
			tile *getTile(int x, int y);
			Map(int width, int height);
			~Map();
			void print_map();

	};




#endif