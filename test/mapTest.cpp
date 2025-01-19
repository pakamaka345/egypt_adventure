#include <iostream>
#include <ctime>
#include <cstdlib>
#include <entities/Entity.hpp>
#include <items/Item.hpp>
#include "map/MapGenerator.hpp"
#include "map/Map.hpp"
#include "states/LevelState.hpp"
#include "tiles/Tile.hpp"

int main() {
    srand(time(NULL));
    auto level = MapGenerator::GenerateMap(2, 200, 200, 20, 25, 10);

    auto map = level->getMap();

    int width = map->getWidth();
    int height = map->getHeight();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto tile = map->getTile(x, y);
            if (tile->hasEntity()) {
                std::cout << tile->getEntity()->getSymbol();
                continue;
            }
            if (tile->hasItems()) {
                std::cout << tile->getItem()->getSymbol();
                continue;
            }

            std::cout << tile->getSymbol();
        }
        std::cout << std::endl;
    }

    return 0;
}