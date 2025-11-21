
#include "connection_rules.hpp"

void initRules(){
	ruleTable[(int) tiletype::PLAIN] = plainRules;
	ruleTable[(int) tiletype::RIVER] = riverRules;
	ruleTable[(int) tiletype::ROAD] = roadRules;
	ruleTable[(int) tiletype::FOREST] = forestRules;
}

void randomlyAssignNeighbourstypes(Map* map, int x, int y, std::vector<tiletype> allowed){
	std::vector<tile*> neighbours = map->getNeighbours(x, y);
	std::vector<tile*>::iterator it;
	for (it = neighbours.begin(); it != neighbours.end(); it++){
		if ((*it)->type == NONE){
			int next_type = flat_int_random(global_rng, 0, allowed.size() - 1);
			(*it)->type = allowed[next_type];
		}
	}
}

void pickRandomContinuingNeighbour(Map* map, int x, int y, tiletype continuingType){
	std::vector<tile*> neighbours = map->getNeighbours(x, y);
	std::vector<tile*>::iterator it;
	bool hasNONE = false;
	for (it = neighbours.begin(); it != neighbours.end(); it++){
		if ((*it)->type == NONE){
			hasNONE = true;
			break;
		}
	}
	while (hasNONE){
		int randomDirection = flat_int_random(global_rng, 0, neighbours.size() - 1);
		if (neighbours[randomDirection]->type == NONE){
			neighbours[randomDirection]->type = continuingType;
			return;
		}
	}
}

void plainRules(Map* map, int x, int y){
	std::vector<tiletype> allowed {PLAIN, RIVER, FOREST, ROAD};
	randomlyAssignNeighbourstypes(map, x, y, allowed);
}

void riverRules(Map* map, int x, int y){
	std::vector<tiletype> allowed {PLAIN, FOREST};
	pickRandomContinuingNeighbour(map, x, y, RIVER);
	randomlyAssignNeighbourstypes(map, x, y, allowed);
}

void forestRules(Map* map, int x, int y){
	std::vector<tiletype> allowed {PLAIN, FOREST};
	randomlyAssignNeighbourstypes(map, x, y, allowed);
}

void roadRules(Map* map, int x, int y){
	std::vector<tiletype> allowed {PLAIN, FOREST};
	pickRandomContinuingNeighbour(map, x, y, ROAD);
	randomlyAssignNeighbourstypes(map, x, y, allowed);
}
