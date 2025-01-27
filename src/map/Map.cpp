#include "map/Map.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <dice/DiceRoll.hpp>
#include <utility>
#include "entities/Character.hpp"
#include "items/Bullet.hpp"
#include "tiles/WallTile.hpp"
#include "tiles/FloorTile.hpp"
#include "tiles/BedrockTile.hpp"

Map::Map(int width, int height, int levelIndex)
    : width(width), height(height)
{
    map.resize(height);
    staticLightMap.resize(height);
    dynamicLightMap.resize(height);
    seenMap.resize(height);
    for (int y = 0; y < height; y++)
    {
        map[y].resize(width);
        staticLightMap[y].resize(width);
        dynamicLightMap[y].resize(width);
        seenMap[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
            {
                map[y][x] = std::make_shared<BedrockTile>(x, y, levelIndex);
                staticLightMap[y][x] = LightType::STATIC;
                seenMap[y][x] = true;
            } else
            {
                map[y][x] = std::make_shared<WallTile>(x, y, levelIndex);
                staticLightMap[y][x] = LightType::NONE;
            }
        }
    }
}

Map::Map(const Map &generatedMap)
{
    this->map = generatedMap.map;
    this->width = generatedMap.width;
    this->height = generatedMap.height;
    this->leaves = generatedMap.leaves;
    this->rooms = generatedMap.rooms;
    this->dynamicLightMap = generatedMap.dynamicLightMap;
    this->staticLightMap = generatedMap.staticLightMap;
    this->seenMap = generatedMap.seenMap;
}

Map::Map(std::string& pathToInitFile) : width(0), height(0)
{
    initMap(pathToInitFile);
}

bool Map::canPlaceItem(const int x, const int y) const
{
    if (isInsideMap(x, y))
        return true;
    return false;
}

bool Map::canPlaceEntity(const int x, const int y) const
{
    if (isInsideMap(x, y))
        return (!map[y][x]->hasEntity() && map[y][x]->isWalkable());
    return false;
}

void Map::placeItem(const int x, const int y, std::shared_ptr<Item> item) const
{
    if (canPlaceItem(x, y))
    {
        map[y][x]->addItem(std::move(item));
    } else {
        throw std::runtime_error("Could not place item at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::placeEntity(const int x, const int y, std::shared_ptr<Entity> entity) const
{
    if (canPlaceEntity(x, y))
    {
        map[y][x]->setEntity(std::move(entity));
    } else {
        throw std::runtime_error("Could not place entity at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::removeItem(int x, int y)
{
    if (isInsideMap(x, y) && map[y][x]->hasItems())
    {
        map[y][x]->removeItem();
    } else {
        throw std::runtime_error("Could not remove item at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::removeEntity(int x, int y)
{
    if (isInsideMap(x, y) && map[y][x]->hasEntity())
    {
        map[y][x]->removeEntity();
    } else {
        throw std::runtime_error("Could not remove entity at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

std::shared_ptr<Entity> Map::getEntityAt(const int x, const int y) const
{
    if (map[y][x]->hasEntity()) {
        return map[y][x]->getEntity();
    }
    return nullptr;
}

std::shared_ptr<Item> Map::getItemAt(const int x, const int y) const
{
    if (map[y][x]->hasItems()) {
        return map[y][x]->getItem();
    }
    return nullptr;
}

std::vector<Position> Map::getFreePositionsAround(const int x, const int y, const int radius, const int count) const {
    std::vector<Position> freePositions;
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            if (
                    Position candidate(x + dx, y + dy);
                    canPlaceEntity(candidate.x, candidate.y) && (dx != 0 || dy != 0)
                ) {
                freePositions.emplace_back(candidate);
                if (freePositions.size() == count) {
                    return freePositions;
                }
            }
        }
    }
    return freePositions;
}

Position Map::getRandomFreePosition(const int x, const int y, const int radius) const
{
    DiceRoll gen;
    std::vector<Position> freePositions;

    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            if (
                    Position candidate(x + dx, y + dy);
                    canPlaceEntity(candidate.x, candidate.y)
                ) {
                freePositions.push_back(candidate);
            }
        }
    }

    if (freePositions.empty()) {
        return {-1, -1};
    }

    return freePositions[gen.randomNumber(0, static_cast<int>(freePositions.size()) - 1)];
}

std::vector<std::shared_ptr<Tile>> Map::getAdjacentTiles(int x, int y) const
{
    std::vector<std::shared_ptr<Tile>> adjacentTiles;

    const std::vector<Position> offsets = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };

    for (const auto& position : offsets) {
        int nx = x + position.x;
        int ny = y + position.y;

        if (isInsideMap(nx, ny)) {
            adjacentTiles.push_back(getTile(nx, ny));
        }
    }

    return adjacentTiles;
}

std::shared_ptr<Tile> Map::getTileInDirection(int x, int y, Direction direction) const
{
    int dx = 0, dy = 0;

    switch (direction) {
        case Direction::UP:
            dy = -1;
            break;
        case Direction::DOWN:
            dy = 1;
            break;
        case Direction::LEFT:
            dx = -1;
            break;
        case Direction::RIGHT:
            dx = 1;
            break;
        default:
            break;
    }

    const int targetX = x + dx;
    const int targetY = y + dy;

    if (isInsideMap(targetX, targetY)) {
        return getTile(targetX, targetY);
    }

    return nullptr;
}

void Map::listEntitiesAndItems(const std::string& pathToWrite)
{
    std::ofstream file(pathToWrite, std::ios::out);
    if (file.is_open())
    {
        file << "Entities:\n";


        file.close();
    } else {
        throw std::runtime_error("Could not open file to write entities and items\n");
    }
}

bool Map::isInsideMap(int x, int y) const {
    return x > 0 && x < width - 1 && y > 0 && y < height - 1;
}

void Map::setTile(const std::shared_ptr<Tile>& tile)
{
    int x = tile->getX();
    int y = tile->getY();
    if (isInsideMap(x, y))
        map[y][x] = tile;
    else
        throw std::runtime_error("Could not set tile at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
}

std::shared_ptr<Tile> Map::getTile(const int x, const int y) const {
    return map[y][x];
}



Position Map::getPositionNearStair()
{
    const auto startRoom = rooms[0];
    Position stairPos(-1, -1);
    for (int dx = startRoom->x; dx <=startRoom->x + startRoom->width; dx++) {
        for (int dy = startRoom->y; dy <=startRoom->y + startRoom->height; dy++) {
            if (getTile(dx, dy)->getTileType() == TileType::STAIRS) {
                stairPos = {dx, dy};
            }
        }
    }

    if (stairPos == Position(-1, -1)) {
        auto freePos = getRandomFreePosition(startRoom->getCenter().x, startRoom->getCenter().y, 5);
        if (freePos == Position(-1, -1)) {
            throw std::runtime_error("Could not find a free position for start room\n");
        }
        return freePos;
    }

    for (int dx = stairPos.x - 1; dx <= stairPos.x + 1; dx++) {
        for (int dy = stairPos.y - 1; dy <= stairPos.y + 1; dy++) {
            if (canPlaceEntity(dx, dy) && dx != stairPos.x && dy != stairPos.y) {
                return {dx, dy};
            }
        }
    }

    return {-1, -1};
}

void Map::setStaticLight(int x, int y, LightType lightType)
{
    if (isInsideMap(x, y)) {
        staticLightMap[y][x] = lightType;
    }
}

void Map::setDynamicLight(int x, int y, LightType lightType)
{
    if (isInsideMap(x, y)) {
        dynamicLightMap[y][x] = lightType;
    }
}

LightType Map::getStaticLight(int x, int y) const
{
    return isInsideMap(x, y) ? staticLightMap[y][x] : LightType::NONE;
}

LightType Map::getDynamicLight(int x, int y) const
{
    return isInsideMap(x, y) ? dynamicLightMap[y][x] : LightType::NONE;
}

void Map::markAsSeen(int x, int y)
{
    if (isInsideMap(x, y)) {
        seenMap[y][x] = true;
    }
}

bool Map::isSeen(int x, int y) const
{
    return isInsideMap(x, y) ? seenMap[y][x] : false;
}



void Map::initMap(std::string& pathToInitFile)
{
    std::ifstream file(pathToInitFile, std::ios::in);
    //file.imbue(std::locale("en_US.UTF-8"));
    if (file.is_open())
    {
        file >> width >> height;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        map.resize(height);
        for (int y = 0; y < height; y++)
        {
            map[y].resize(width);
        }
        for (int y = 0; y < height; y++)
        {
            std::string line;
            std::getline(file, line); 
            for (int x = 0; x < width; x++)
            {
                switch (line[x])
                {
                    case '#': {
                        std::shared_ptr<Tile> wall = std::make_shared<WallTile>(x, y, 0);
                        map[y][x] = wall;
                        break;
                    }
                    case ' ': {
                        std::shared_ptr<Tile> floor = std::make_shared<FloorTile>(x, y, 0);
                        map[x][y] = floor;
                        break;
                    }
                    case '@': {
                        std::shared_ptr<Tile> floor = std::make_shared<FloorTile>(x, y, 0);
                        map[x][y] = floor;
                        std::shared_ptr<Entity> player = std::make_shared<Character>("Piter Miller", x, y, 0, '@');
                        placeEntity(x, y, player);
                        break;
                    }
                    case 'B': {
                        std::shared_ptr<Tile> floor = std::make_shared<FloorTile>(x, y, 0);
                        map[x][y] = floor;
                        std::shared_ptr<Item> bullet = std::make_shared<Bullet>(25.0f, 0.0f, 0);
                        placeItem(x, y, bullet);
                        break;
                    }
                    default:  
                        throw std::runtime_error("Unexpected character in map file at (" + std::to_string(x) + ", " + std::to_string(y) + ") the character is: " + line[y] + "\n");
                }
            }
        }
        std::cout << "Map initialized successfully\n";
        file.close(); 
    }
    else
    {
        throw std::runtime_error("Could not open file to initialize map\n");
    }
}

