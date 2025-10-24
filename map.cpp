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
	std::vector<tile*> creation_order = this->create_tile_creation_order();
	std::vector<tile*>::iterator current;
	std::vector<tiletype> tileset;
	fill_tileset(tileset);

	std::cout << "creation order size: " << creation_order.size() << std::endl;
	current = creation_order.begin();
	(*current)->name = tileset[flat_int_random(global_rng, 0, tileset.size() - 1)];
	while (current != creation_order.end()){
		link_tiles(**current);
		current++;
	}
}

std::vector<tile*> Map::create_tile_creation_order(){
	int start_x = flat_int_random(global_rng, 0, this->width - 1);
	int start_y = flat_int_random(global_rng, 0, this->height - 1);
	std::vector<tile*> creation_order = {};
	unsigned long i = 0;

	creation_order.push_back(this->map[start_x][start_y]);
	unsigned long total_tiles = this->height * this->width;

	while (creation_order.size() < total_tiles && i < creation_order.size()){
		if( (creation_order[i])->seen == false){
			(creation_order[i])->add_to_queue(&creation_order);
		}
		i++;
	}
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
