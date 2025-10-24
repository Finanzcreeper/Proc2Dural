
#include "tile.hpp"
#include "map.hpp"
#include <iostream>

std::mt19937 global_rng = create_rng();

int main(int argc, char* argv[]) {
	int Xmax = 0;
	int Ymax = 0;
	if (argc != 3) {
		std::cout << "using standard map size 3x3, to change run program with two args, x and y" << std::endl;
		Xmax = 3;
		Ymax = 3;
	} else {
		Xmax = std::stoi(argv[1]);
		Ymax = std::stoi(argv[2]);
	}
	std::cout << "creating Map" << std::endl;
	Map *map = new Map(Xmax, Ymax);
	std::cout << "discovering tiles" << std::endl;
	map->discover_tile_types();
	std::cout << "printing map" << std::endl;
	map->print_map();
}
