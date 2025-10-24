#include "map.hpp"

Map::Map(int width, int height){
	this->width = width;
	this->height = height;
	this->map.resize(width);
	for (int w = 0; w < width; w++ ){
		this->map[w].resize(height, nullptr);
		for (int h = 0; h < height; h++){
			this->map[w][h] = new tile();
			if (w - 1 >= 0){
				this->map[w][h]->connect(this->map[w - 1][h], direction::up);
			}
			if (h - 1 >= 0){
				this->map[w][h]->connect(this->map[w][h - 1], direction::left);
			}
		}
	}
	for (int w = 0; w < width; w++ ){
		for (int h = 0; h < height; h++){
			this->map[w][h]->fill_directions();
		}
	}

}

Map::~Map(){
	std::vector<std::vector<tile*>>::iterator it = this->map.begin();
	std::vector<tile*>::iterator inner_it;
	while(it != this->map.end()){
		inner_it = it->begin();
		while( inner_it != it->end()){
			if (*inner_it != NULL){
				delete *inner_it;
				*inner_it = NULL;
			}
			inner_it++;
		}
		it++;
	}
}

void Map::discover_tile_types(){
	std::queue<tile*> creation_order = this->create_tile_creation_order();
	tile* current;
	std::vector<tiletype> tileset;
	fill_tileset(tileset);
	std::cout << "tiles discovery setup done" << std::endl;

	current = creation_order.front();
	current->name = tileset[flat_int_random(global_rng, 0, tileset.size() - 1)];
	std::cout << "first tile discovered" << std::endl;
	link_tiles(*current);
	std::cout << "first tile linked" << std::endl;
	creation_order.pop();
	std::cout << "discovering new tiles" << std::endl;
	while (creation_order.empty() == false){
		current = creation_order.front();
		link_tiles(*current);
		creation_order.pop();
	}
}

std::queue<tile*> Map::create_tile_creation_order(){
	int start_x = flat_int_random(global_rng, 0, this->width - 1);
	int start_y = flat_int_random(global_rng, 0, this->height - 1);
	std::queue<tile*> creation_order = {};
	std::cout << "tile creation order setup done" << std::endl;
	this->map[start_x][start_y]->add_to_queue(&creation_order);
	std::cout << "tile creation order found" << std::endl;
	return creation_order;
}

void Map::print_map() {
	int x = 0;
	int y = 0;
	while (x < this->width) {
		while (y < this->height) {
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