#pragma once 
#include <utility>
#include <vector>
#include <memory>
#include "commands/MoveCommand.hpp"
#include "RoomGenerator.hpp"

class Tile;
class Entity;
class Item;
class RoomGenerator;
class BSPNode;

enum class LightType
{
    NONE,
    STATIC,
    DYNAMIC
};

class Map
{
protected:
    std::vector<std::vector<std::shared_ptr<Tile>>> map;
    std::vector<std::vector<LightType>> staticLightMap;
    std::vector<std::vector<LightType>> dynamicLightMap;
    std::vector<std::vector<bool>> seenMap;
    std::vector<std::shared_ptr<RoomGenerator::Room>> rooms;
    std::vector<std::shared_ptr<BSPNode>> leaves;
    int width;
    int height;

public:
    explicit Map(std::string& pathToInitFile);
    Map(const Map& generatedMap);
    Map(int width, int height, int levelIndex);
    ~Map() = default;

    [[nodiscard]] bool canPlaceItem(int x, int y) const;
    [[nodiscard]] bool canPlaceEntity(int x, int y) const;

    void placeItem(int x, int y, std::shared_ptr<Item> item) const;
    void placeEntity(int x, int y, std::shared_ptr<Entity> entity) const;

    void removeItem(int x, int y);
    void removeEntity(int x, int y);

    [[nodiscard]] std::shared_ptr<Entity> getEntityAt(int x, int y) const;
    [[nodiscard]] std::shared_ptr<Item> getItemAt(int x, int y) const;

    [[nodiscard]] std::vector<Position> getFreePositionsAround(int x, int y, int radius, int count) const;
    [[nodiscard]] Position getRandomFreePosition(int x, int y, int radius) const;
    [[nodiscard]] std::vector<std::shared_ptr<Tile>> getAdjacentTiles(int x, int y) const;
    std::shared_ptr<Tile> getTileInDirection(int x, int y, Direction direction) const;

    void listEntitiesAndItems(const std::string& pathToWrite);

    [[nodiscard]] bool isInsideMap(int x, int y) const;
    void setTile(const std::shared_ptr<Tile>& tile);
    [[nodiscard]] std::shared_ptr<Tile> getTile(int x, int y) const;

    void setRooms(const std::vector<std::shared_ptr<RoomGenerator::Room>>& rooms) { this->rooms = rooms; }
    std::vector<std::shared_ptr<RoomGenerator::Room>>& getRooms() { return rooms; }

    void setLeaves(std::vector<std::shared_ptr<BSPNode>> leaves) { this->leaves = std::move(leaves); }
    std::vector<std::shared_ptr<BSPNode>>& getLeaves() { return leaves; }

    Position getPositionNearStair();

    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }

    void setStaticLight(int x, int y, LightType lightType);
    void setDynamicLight(int x, int y, LightType lightType);
    LightType getStaticLight(int x, int y) const;
    LightType getDynamicLight(int x, int y) const;

    void markAsSeen(int x, int y);
    bool isSeen(int x, int y) const;

private:
    void initMap(std::string& pathToInitFile);
};