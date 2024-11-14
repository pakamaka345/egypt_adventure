#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "entities/Player.hpp"
#include "items/Torch.hpp"
#include <limits>

Map::Map(int width, int height)
    : width(width), height(height)
{
    map.resize(height);
    for (int y = 0; y < height; y++)
    {
        map[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            map[y][x].setTileType(TileType::TileType::WALL);
        }
    }
}

Map::Map(std::string pathToInitFile)
{
    initMap(pathToInitFile);
}

bool Map::canPlaceItem(int x, int y, std::unique_ptr<Item>& item)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return !map[y][x].hasItem() && item->canBePlacedOn(map[y][x].getTileType());
    return false;
}

bool Map::canPlaceEntity(int x, int y, std::unique_ptr<Entity>& entity)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return !map[y][x].hasEntity();
    return false;
}

void Map::placeItem(int x, int y, std::unique_ptr<Item> item) 
{
    if (canPlaceItem(x, y, item))
    {
        map[y][x].setItem(std::move(item));
    } else {
        throw std::runtime_error("Could not place item at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::placeEntity(int x, int y, std::unique_ptr<Entity> entity)
{
    if (canPlaceEntity(x, y, entity))
    {
        map[y][x].setEntity(std::move(entity));
    } else {
        throw std::runtime_error("Could not place entity at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::removeItem(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[x][y].hasItem())
    {
        map[y][x].removeItem();
    } else {
        throw std::runtime_error("Could not remove item at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::removeEntity(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[x][y].hasEntity())
    {
        map[y][x].removeEntity();
    } else {
        throw std::runtime_error("Could not remove entity at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
    }
}

void Map::listEntitiesAndItems(std::string pathToWrite)
{
    std::ofstream file(pathToWrite, std::ios::out);
    if (file.is_open())
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (map[y][x].hasEntity())
                {
                    file << "Entity: " << map[y][x].getEntity()->getName() << " at (" << x << ", " << y << ")\n";
                }
                if (map[y][x].hasItem())
                {
                    file << "Item: " << map[y][x].getItem()->getName() << " at (" << x << ", " << y << ")\n";
                }
            }
        }
        file.close();
    } else {
        throw std::runtime_error("Could not open file to write entities and items\n");
    }
}

void Map::initMap(std::string pathToInitFile)
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
                    case '#':  
                        map[y][x].setTileType(TileType::TileType::WALL);
                        break;
                    case ' ':  
                        map[y][x].setTileType(TileType::TileType::FLOOR);
                        break;
                     case '@': 
                         map[y][x].setTileType(TileType::TileType::FLOOR);
                         placeEntity(x, y, std::make_unique<Player>("Piter Miller", 100, 10, '@', x, y));
                         break;
                     case 'T': 
                         map[y][x].setTileType(TileType::TileType::WALL);
                         placeItem(x, y, std::make_unique<Torch>("Torch", 1, true, 'T', x, y));
                         break;
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

void Map::setTile(int x, int y, TileType::TileType TileType)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        map[y][x].setTileType(TileType);
    else 
        throw std::runtime_error("Could not set tile at (" + std::to_string(x) + ", " + std::to_string(y) + ")\n");
}