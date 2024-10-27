#include "Tile.hpp"
#include <iostream>

Tile::Tile()
    : TileType(TileType::TileType::FLOOR)
    , entity(nullptr)
    , item(nullptr)
{
    setSymbol(TileType::TileType::FLOOR);
}

Tile::Tile(TileType::TileType TileType)
    : TileType(TileType)
    , entity(nullptr)
    , item(nullptr)
{
    setSymbol(TileType);
}

void Tile::setEntity(std::unique_ptr<Entity> entity)
{
    this->entity = std::move(entity);
}

void Tile::setItem(std::unique_ptr<Item> item)
{
    this->item = std::move(item);
}

std::unique_ptr<Entity> Tile::getEntity()
{
    return std::move(entity);
}

std::unique_ptr<Item> Tile::getItem()
{
    return std::move(item);
}

TileType::TileType Tile::getTileType()
{
    return TileType;
}

void Tile::setTileType(TileType::TileType TileType)
{
    this->TileType = TileType;
    setSymbol(TileType);
}

bool Tile::hasEntity()
{
    return entity != nullptr;
}

bool Tile::hasItem()
{
    return item != nullptr;
}

void Tile::removeEntity()
{
    if (hasEntity()) entity.reset();
}

void Tile::removeItem()
{
    if (hasItem()) item.reset();    
}

void Tile::draw()
{
    if (hasEntity()) 
    {
        entity->draw();
        return;
    }
    else if (hasItem()) 
    {
        item->draw();
        return;
    }
    else
    {
        std::cout << symbol;
    }
}

char Tile::getSymbol()
{
    return symbol;
}   

bool Tile::isWalkable()
{
    return TileType != TileType::TileType::WALL;
}

void Tile::setSymbol(TileType::TileType TileType) 
{
    switch (TileType)
    {
        case TileType::TileType::FLOOR:
            symbol = ' ';
            break;
        case TileType::TileType::WALL:
            symbol = char(178);
            break;
    }
}