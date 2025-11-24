#include "map.hpp"


void Map::addValidNeighbour(int x, int y, std::vector<tile*> &neighbours){
	tile* neighbour;
	try {
		neighbour = getTile(x, y);
	}
	catch(const std::invalid_argument& e){
		std::cout << e.what() << std::endl;
		return;
	}
	neighbours.push_back(neighbour);
}

tile* Map::getTile(int x, int y){
	if (!inBounds(x, y)){
		throw std::invalid_argument("Tile not in bounds");
	}
	return &this->map[x][y];
}

bool Map::inBounds(int x, int y){
	return x >= 0 && x< this->width && y >= 0 && y < this->height;
}

std::vector<tile*> Map::getNeighbours(int x, int y){
	std::vector<tile*> neighbours = {};
	if (!inBounds(x, y)){
		throw std::invalid_argument("Coordinates not in bounds");
	}
	addValidNeighbour(x - 1, y, neighbours);
	addValidNeighbour(x + 1, y, neighbours);
	addValidNeighbour(x, y - 1, neighbours);
	addValidNeighbour(x, y + 1, neighbours);
	return neighbours;
}

Map::Map(int width, int height) : width(width), height(height) {
    if (width <= 0 || height <= 0){
        throw std::invalid_argument("cannot create map with negative width or height");
    }
	tile noneTile;
	noneTile.type = NONE;
    map.resize(width, std::vector<tile>(height, noneTile));
}

Map::~Map(){}

void Map::print_map() {
	int x = 0;
	int y = 0;
	while (x < this->width) {
		while (y < this->height) {
			switch (this->map[x][y].type) {
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
