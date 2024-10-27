#pragma once 
#include <vector>
#include "Tile.hpp"

class Map
{
private: 
    std::vector<std::vector<Tile>> map;
    int width;
    int height;

public:
    Map(std::string pathToInitFile);
    Map(int width, int height);
    ~Map() = default;

    bool canPlaceItem(int x, int y, std::unique_ptr<Item>& item);
    bool canPlaceEntity(int x, int y, std::unique_ptr<Entity>& entity);

    void placeItem(int x, int y, std::unique_ptr<Item> item);
    void placeEntity(int x, int y, std::unique_ptr<Entity> entity);

    void removeItem(int x, int y);
    void removeEntity(int x, int y);

    void listEntitiesAndItems(std::string pathToWrite);

    void draw();

    void setTile(int x, int y, TileType::TileType TileType);

private:
    void initMap(std::string pathToInitFile);
};