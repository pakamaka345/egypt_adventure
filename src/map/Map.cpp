#include "map/Map.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <dice/DiceRoll.hpp>

#include "entities/Character.hpp"
#include "items/Bullet.hpp"
#include "tiles/WallTile.hpp"
#include "tiles/FloorTile.hpp"
#include "tiles/BedrockTile.hpp"

Map::Map(int width, int height)
    : width(width), height(height)
{
    map.resize(height);
    for (int y = 0; y < height; y++)
    {
        map[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
            {
                map[y][x] = std::make_shared<BedrockTile>(x, y);
            } else
            {
                map[y][x] = std::make_shared<WallTile>(x, y);
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
}

Map::Map(std::string& pathToInitFile) : width(0), height(0)
{
    initMap(pathToInitFile);
}

bool Map::canPlaceItem(int x, int y)
{
    if (x > 0 && x < width - 2 && y > 0 && y < height - 2)
        return true;
    return false;
}

bool Map::canPlaceEntity(int x, int y)
{
    if (x > 0 && x < width - 2 && y > 0 && y < height - 2)
        return (!map[y][x]->hasEntity() && map[y][x]->isWalkable());
    return false;
}

void Map::placeItem(int x, int y, std::shared_ptr<Item>& item)
{
    if (canPlaceItem(x, y))
    {
        map[y][x]->addItem(item);
    } else {
        throw std::runtime_error("Could not place item at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::placeEntity(int x, int y, std::shared_ptr<Entity>& entity)
{
    if (canPlaceEntity(x, y))
    {
        map[y][x]->setEntity(entity);
    } else {
        throw std::runtime_error("Could not place entity at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::removeItem(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[x][y]->hasItems())
    {
        map[y][x]->removeItem();
    } else {
        throw std::runtime_error("Could not remove item at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::removeEntity(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[x][y]->hasEntity())
    {
        map[y][x]->removeEntity();
    } else {
        throw std::runtime_error("Could not remove entity at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

std::vector<Position> Map::getFreePositionsAround(int x, int y, int radius, int count) {
    std::vector<Position> freePositions;
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            Position candidate(x + dx, y + dy);
            if (canPlaceEntity(candidate.x, candidate.y) && (dx != 0 || dy != 0)) {
                freePositions.emplace_back(candidate);
                if (freePositions.size() == count) {
                    return freePositions;
                }
            }
        }
    }
    return freePositions;
}

Position Map::getRandomFreePosition(int x, int y, int radius)
{
    DiceRoll gen;
    std::vector<Position> freePositions;

    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            Position candidate(x + dx, y + dy);
            if (canPlaceEntity(candidate.x, candidate.y)) {
                freePositions.push_back(candidate);
            }
        }
    }

    if (freePositions.empty()) {
        return {-1, -1};
    }

    return freePositions[gen.randomNumber(0, static_cast<int>(freePositions.size()) - 1)];
}


void Map::listEntitiesAndItems(std::string& pathToWrite)
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

bool Map::isInsideMap(int x, int y) {
    if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
        return true;
    return false;
}

void Map::setTile(std::shared_ptr<Tile> tile)
{
    int x = tile->getX();
    int y = tile->getY();
    if (isInsideMap(x, y))
        map[y][x] = tile;
    else
        throw std::runtime_error("Could not set tile at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
}

std::shared_ptr<Tile>& Map::getTile(int x, int y) {
    return map[y][x];
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
                        std::shared_ptr<Tile> wall = std::make_shared<WallTile>(x, y);
                        map[y][x] = wall;
                        break;
                    }
                    case ' ': {
                        std::shared_ptr<Tile> floor = std::make_shared<FloorTile>(x, y);
                        map[x][y] = floor;
                        break;
                    }
                    case '@': {
                        std::shared_ptr<Tile> floor = std::make_shared<FloorTile>(x, y);
                        map[x][y] = floor;
                        std::shared_ptr<Entity> player = std::make_shared<Character>("Piter Miller", x, y, '@');
                        placeEntity(x, y, player);
                        break;
                    }
                    case 'B': {
                        std::shared_ptr<Tile> floor = std::make_shared<FloorTile>(x, y);
                        map[x][y] = floor;
                        std::shared_ptr<Item> bullet = std::make_shared<Bullet>(25.0f, 0.0f, "bullet",
                                                                                "simple round bullet", x, y, 'B');
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

