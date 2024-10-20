#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

Map::Map(int width, int height)
    : width(width), height(height)
{
}

Map::Map(std::string pathToInitFile)
{
    initMap(pathToInitFile);
}

bool Map::canPlaceItem(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return !map[x][y].hasItem();
    return false;
}

bool Map::canPlaceEntity(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return !map[x][y].hasEntity();
    return false;
}

void Map::placeItem(int x, int y, std::unique_ptr<Item> item) 
{
    if (canPlaceItem(x, y))
    {
        map[x][y].setItem(std::move(item));
    } else {
        std::cerr << "Could not place item at (" << x << ", " << y << ")\n";
    }
}

void Map::placeEntity(int x, int y, std::unique_ptr<Entity> entity)
{
    if (canPlaceEntity(x, y))
    {
        map[x][y].setEntity(std::move(entity));
    } else {
        std::cerr << "Could not place entity at (" << x << ", " << y << ")\n";
    }
}

void Map::removeItem(int x, int y)
{
    if (map[x][y].hasItem() || x >= 0 && x < width && y >= 0 && y < height)
    {
        map[x][y].removeItem();
    } else {
        std::cerr << "Could not remove item at (" << x << ", " << y << ")\n";
    }
}

void Map::removeEntity(int x, int y)
{
    if (map[x][y].hasEntity() || x >= 0 && x < width && y >= 0 && y < height)
    {
        map[x][y].removeEntity();
    } else {
        std::cerr << "Could not remove entity at (" << x << ", " << y << ")\n";
    }
}

void Map::listEntitiesAndItems(std::string pathToWrite)
{
    std::ofstream file(pathToWrite, std::ios::out);
    if (file.is_open())
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                if (map[x][y].hasEntity())
                {
                    file << "Entity: " << map[x][y].getEntity()->getName() << " at (" << x << ", " << y << ")\n";
                }
                if (map[x][y].hasItem())
                {
                    file << "Item: " << map[x][y].getItem()->getName() << " at (" << x << ", " << y << ")\n";
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Could not open file to write entities and items\n";
    }
}

void Map::draw()
{
    std::cout << "----------------------------------------------------\n";
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            map[x][y].draw(); 

        }
    }
    //TODO after I add the player class and it will be dynamic
    std::cout << "Piter Miller\n";
    std::cout << "Info: \n";
    std::cout << "Health: 100\n"; 
    std::cout << "Ammo: 6/6\n";
    std::cout << "light 1:14";
    std::cout << "3 artifacts are active\n";
    std::cout << "press 'I' to open inventory\n";
    std::cout << "w,a,s,d to move\n";
    std::cout << "'e' to interact\n";
    std::cout << "----------------------------------------------------\n";
}

void Map::initMap(std::string pathToInitFile)
{
    std::ifstream file(pathToInitFile, std::ios::in);

    if (file.is_open())
    {
        file >> width >> height;
        map.resize(width);
        for (int x = 0; x < width; x++)
        {
            map[x].resize(height);
            for (int y = 0; y < height; y++)
            {
                switch (file.get())
                {
                    case char(178):
                        map[x][y].setPoleType(PoleType::PoleType::WALL);
                        break;
                    case ' ':
                        map[x][y].setPoleType(PoleType::PoleType::FLOOR);
                        break;
                    case '@': 
                        map[x][y].setPoleType(PoleType::PoleType::FLOOR);
                        placeEntity(x, y, std::make_unique<Player>("Piter Miller", 100, 10, '@'));
                        break;
                    case 'T':
                        map[x][y].setPoleType(PoleType::PoleType::FLOOR);
                        placeItem(x, y, std::make_unique<Torch>("Torch", 1, true, 'T'));
                        break;
                }
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Could not open file to read map\n";
    }
}

void Map::setPole(int x, int y, PoleType::PoleType poleType)
{
    map[x][y].setPoleType(poleType);
}