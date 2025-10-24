#include "tile.hpp"

void tile::fill_directions() {
	this->directions[0] = this->up;
	this->directions[1] = this->down;
	this->directions[2] = this->left;
	this->directions[3] = this->right;
}

void tile::generate_connections()
{
	link_tiles(*this);
	this->seen = true;
	std::vector<tile*>::iterator it = this->directions.begin();
	while (it != this->directions.end()){
		if ((*it) != NULL && (*it)->seen == false) {
			(*it)->generate_connections();
		}
		++it;
	}
}

void tile::connect(tile* a, direction dir){
	if (!a){
		return ;
	}
	switch (dir){
		case direction::up:
			this->up = a;
			a->down = this;
			break;
		case direction::left:
			this->left = a;
			a->right = this;
			break;
		default:
			std::cout << "not defined connection" << std::endl;
			break;
	}
}

void tile::add_to_queue(std::vector<tile*> *queue){
	if (this->seen == true){
		return ;
	}
	this->seen = true;
	std::vector<tile*>::iterator it = this->directions.begin();
	while (it != this->directions.end()){
		if (*it != NULL && (*it)->vectorContains(queue) == false){
			queue->push_back(*it);
		}
		it++;
	}
}

bool tile::vectorContains(const std::vector<tile*>* vector){
	bool state = std::find(vector->begin(), vector->end(), this) != vector->end();
	return state;
}


tile::tile():left(NULL), up(NULL), right(NULL), down(NULL), name(NONE) {
}

tile::~tile() {
}