#include "tile.hpp"
#include <iostream>

void print_map(int w, int h, std::vector<std::vector<tile *>> map);
void init_map(int w, int h, std::vector<std::vector<tile *>> &map);

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
	std::vector<std::vector<tile *>> map = {};
	std::vector<tiletype> tileset;
	std::mt19937 rng = create_rng();
	int x = 0;
	int y = 0;
		

	fill_tileset(tileset);
	init_map(Xmax, Ymax, map);

	x = flat_int_random(rng, 0, Xmax - 1);
	y = flat_int_random(rng, 0, Ymax - 1);
	std::cout << "starting at x:" << x << " y:" << y << std::endl;

	int t =  flat_int_random(rng, 0, tileset.size() - 1);
	tiletype a = tileset[t];
	map[x][y]->name = a;
	map[x][y]->generate_connections();
	print_map(Xmax, Ymax, map);
}

void init_map(int w, int h, std::vector<std::vector<tile *>> &map) {
	int x = 0;
	int y = 0;
	// fit map to selected size
	map.resize(w);
	while (x < w) {
		map[x].resize(h);
		++x;
	}
	x = 0;
	y = 0;
	//fill map wiht tiles
	while (x < w) {
		while (y < h) {
			map[x][y] = new tile();
			++y;
		}
		y = 0;
		++x;
	}
	x = 0;
	y = 0;
	//connect tiles with each other
	while (x < w) {
		while (y < h) {
				if (y > 0) {
					map[x][y]->up = map[x][y-1];
				} else {
					map[x][y]->up = NULL;
				}
				if (y < h - 1) {
					map[x][y]->down = map[x][y+1];
				} else {
					map[x][y]->down = NULL;
				}
				if (x > 0) {
					map[x][y]->left = map[x-1][y];
				} else {
					map[x][y]->left = NULL;
				}
				if (x < w - 1) {
					map[x][y]->right = map[x+1][y];
				} else {
					map[x][y]->right = NULL;
				}
				map[x][y]->fill_directions();
			++y;
		}
		y = 0;
		++x;
	}
}

void print_map(int w, int h, std::vector<std::vector<tile *>> map) {
	int x = 0;
	int y = 0;
	while (x < w) {
		while (y < h) {
			switch (map[x][y]->name) {
			case NONE:
				std::cout << " NONE ";
				break;

			case PLAIN:
				std::cout << "PLAIN ";
				break;

			case RIVER:
				std::cout << "RIVER ";
				break;

			case FOREST:
				std::cout << "FOREST";
				break;

			case ROAD:
				std::cout << " ROAD ";
				break;
			
			default:
				break;
			}
			std::cout << "|";
			++y;
		}
		std::cout << "\n";
		y = 0;
		++x;
	}
	std::cout << std::flush;
}