#include "tile.hpp"
#include "random.hpp"


void fill_tileset(std::vector<tiletype> &tileset) {
	tileset.push_back(PLAIN);
	tileset.push_back(RIVER);
	tileset.push_back(FOREST);
	tileset.push_back(ROAD);
}

void link_tiles(tile _tile) {
	switch (_tile.name) {
	case PLAIN:
		plain_rules(_tile);
		break;
	
	case RIVER:
		river_rules(_tile);
		break;

	case FOREST:
		forest_rules(_tile);
		break;

	case ROAD:
		road_rules(_tile);
		break;
	
	default:
		break;
	}
}

bool edge_usable(tile* _tile) {
	if (_tile == NULL) {
		return (false);
	}
	if (_tile->name != NONE) {
		return (false);
	}
	return (true);
}

void connect_edge(tile* _tile){

}

void plain_rules(tile _tile) {
	std::mt19937 rng = create_rng();
	std::vector<tiletype> allowed {PLAIN, RIVER, FOREST, ROAD};
	int i = 0;
	while (i < _tile.directions.size()) {
		if (edge_usable(_tile.directions[i]) != true) {
			++i;
			continue;
		}
		int next_tile = flat_int_random(rng, 0, allowed.size() - 1);
		_tile.directions[i]->name = allowed[next_tile];

		if (allowed[next_tile] == ROAD) {
			allowed.erase(allowed.begin() + next_tile);
		}
		if (allowed[next_tile] == RIVER) {
			allowed.erase(allowed.begin() + next_tile);
		}
		++i;
	}
}

void river_rules(tile _tile) {
	std::mt19937 rng = create_rng();
	std::vector<tiletype> allowed {PLAIN, RIVER, FOREST};
	int i = 0;
	while (i < _tile.directions.size()) {
		if (edge_usable(_tile.directions[i]) != true) {
			++i;
			continue;
		}
		int next_tile = flat_int_random(rng, 0, allowed.size() - 1);
		_tile.directions[i]->name = allowed[next_tile];

		if (allowed[next_tile] == RIVER) {
			allowed.erase(allowed.begin() + next_tile);
		}
		++i;
	}
}

void forest_rules(tile _tile) {
	std::mt19937 rng = create_rng();
	std::vector<tiletype> allowed {PLAIN, FOREST};
	int i = 0;
	while (i < _tile.directions.size()) {
		if (edge_usable(_tile.directions[i]) != true) {
			++i;
			continue;
		}
		int next_tile = flat_int_random(rng, 0, allowed.size() - 1);
		_tile.directions[i]->name = allowed[next_tile];
		++i;
	}
}

void road_rules(tile _tile) {
	std::mt19937 rng = create_rng();
	std::vector<tiletype> allowed {PLAIN, FOREST, ROAD};
	int i = 0;
	while (i < _tile.directions.size()) {
		if (edge_usable(_tile.directions[i]) != true) {
			++i;
			continue;
		}
		int next_tile = flat_int_random(rng, 0, allowed.size() - 1);
		_tile.directions[i]->name = allowed[next_tile];

		if (allowed[next_tile] == ROAD) {
			allowed.erase(allowed.begin() + next_tile);
		}
		++i;
	}
}