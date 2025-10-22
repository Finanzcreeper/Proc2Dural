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

tile::tile():left(NULL), right(NULL), up(NULL), down(NULL), name(NONE) {
}

tile::~tile() {
}