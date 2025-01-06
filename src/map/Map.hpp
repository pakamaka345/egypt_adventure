#pragma once 
#include <vector>
#include <memory>

#include "RoomGenerator.hpp"

class Tile;
class Entity;
class Item;
class Position;
class RoomGenerator;
class BSPNode;

class Map
{
protected:
    std::vector<std::vector<std::shared_ptr<Tile>>> map;
    std::vector<std::shared_ptr<RoomGenerator::Room>> rooms;
    std::vector<std::shared_ptr<BSPNode>> leaves;
    int width;
    int height;

public:
    explicit Map(std::string& pathToInitFile);
    Map(const Map& generatedMap);
    Map(int width, int height);
    ~Map() = default;

    bool canPlaceItem(int x, int y);
    bool canPlaceEntity(int x, int y);

    void placeItem(int x, int y, std::shared_ptr<Item>& item);
    void placeEntity(int x, int y, std::shared_ptr<Entity>& entity);

    void removeItem(int x, int y);
    void removeEntity(int x, int y);

    std::vector<Position> getFreePositionsAround(int x, int y, int radius, int count);
    Position getRandomFreePosition(int x, int y, int radius);

    void listEntitiesAndItems(std::string& pathToWrite);

    bool isInsideMap(int x, int y);
    void setTile(std::shared_ptr<Tile> tile);
    std::shared_ptr<Tile>& getTile(int x, int y);

    void setRooms(std::vector<std::shared_ptr<RoomGenerator::Room>>& rooms) { this->rooms = rooms; }
    std::vector<std::shared_ptr<RoomGenerator::Room>>& getRooms() { return rooms; }

    void setLeaves(std::vector<std::shared_ptr<BSPNode>> leaves) { this->leaves = leaves; }
    std::vector<std::shared_ptr<BSPNode>>& getLeaves() { return leaves; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    void initMap(std::string& pathToInitFile);
};