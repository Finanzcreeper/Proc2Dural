#include "connection_rules.hpp"

tiletype getWeightedRandomTile(std::vector<std::pair<tiletype, unsigned int>> tiles){
    unsigned int totalWeight = getTotalWeight(tiles);
    int random = flat_int_random(global_rng, 0, totalWeight);
    std::vector<std::pair<tiletype, unsigned int>>::iterator it;
    return getRandomTiletype(tiles, random);
}

tiletype getRandomTiletype(std::vector<std::pair<tiletype, unsigned int>> tiles, int random){
    std::vector<std::pair<tiletype, unsigned int>>::iterator it;
    int sum = 0;
    it = tiles.begin();
    while (it != tiles.end()){
        sum += it->second; 
        if (random <= sum){
            return it->first;
        }
        it++;
    }
    return tiles.back().first;
}

unsigned int getTotalWeight(std::vector<std::pair<tiletype, unsigned int>> tiles){
    unsigned int totalWeight = 0;
    std::vector<std::pair<tiletype, unsigned int>>::iterator it;
    it = tiles.begin();
    while (it != tiles.end()){
        totalWeight += it->second;
        it++;
    }
    return totalWeight;
}

