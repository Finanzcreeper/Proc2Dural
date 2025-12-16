#include "map.hpp"
#include "connection-rules/connection_rules.hpp"
#include <iostream>

std::mt19937 global_rng = create_rng();

RuleFunction ruleTable[(int) tiletype::NONE];

void applyRules(Map *map){
	int firstType = flat_int_random(global_rng, 0, numberOfTileTypes() - 2);
	map->getTile(0, 0)->type =  static_cast<tiletype>(firstType);
	for (int x = 0; x < map->width; x++){
		for (int y = 0; y < map->height; y++){
			std::cout << "x=" << x << " y=" << y << std::endl;
			tiletype type = map->getTile(x, y)->type;
			ruleTable[(int) type](map, x, y);
			std::cout << "done" << std::endl;
		}
	}
}


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
	initRules();
	applyRules(map);
	std::cout << "printing map" << std::endl;
	map->print_map();
}
