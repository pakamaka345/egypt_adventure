#pragma once 
#include <vector>
#include <list>
#include "tiles/Tile.hpp"

class Map
{
protected:
    std::vector<std::vector<std::shared_ptr<Tile>>> map;
    std::list<std::shared_ptr<Entity>> entities;
    std::list<std::shared_ptr<Item>> items;
    int width;
    int height;

public:
    explicit Map(std::string& pathToInitFile);
    Map(int width, int height);
    ~Map() = default;

    bool canPlaceItem(int x, int y);
    bool canPlaceEntity(int x, int y);

    void placeItem(int x, int y, std::shared_ptr<Item>& item);
    void placeEntity(int x, int y, std::shared_ptr<Entity>& entity);

    void removeItem(int x, int y);
    void removeEntity(int x, int y);

    std::vector<std::pair<int, int>> getFreePositionsAround(int x, int y, int radius, int count);

    void listEntitiesAndItems(std::string& pathToWrite);

    bool isInsideMap(int x, int y);
    void setTile(std::shared_ptr<Tile>& tile);
    std::shared_ptr<Tile>& getTile(int x, int y);

private:
    void initMap(std::string& pathToInitFile);
};