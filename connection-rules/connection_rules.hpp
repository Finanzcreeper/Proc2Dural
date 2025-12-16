#ifndef CONNECTION_RULES_H
# define CONNECTION_RULES_H

	#include "../tile.hpp"
	#include "../map.hpp"
	#include "../random.hpp"
    #include <vector>



	class Map;
	using RuleFunction = void (*)(Map*, int x, int y);

	extern RuleFunction ruleTable[(int) tiletype::NONE];

	void plainRules(Map* map, int x, int y);
	void riverRules(Map* map, int x, int y);
	void forestRules(Map* map, int x, int y);
	void roadRules(Map* map, int x, int y);
	void initRules();

    tiletype getWeightedRandomTile(std::vector<std::pair<tiletype, unsigned int>> tiles);



#endif