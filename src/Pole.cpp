#include "Pole.hpp"
#include <iostream>

Pole::Pole(PoleType::PoleType poleType)
    : poleType(poleType)
{
    setSymbol(poleType);
}

void Pole::setEntity(std::unique_ptr<Entity> entity)
{
    this->entity = std::move(entity);
}

void Pole::setItem(std::unique_ptr<Item> item)
{
    this->item = std::move(item);
}

std::unique_ptr<Entity> Pole::getEntity()
{
    return std::move(entity);
}

std::unique_ptr<Item> Pole::getItem()
{
    return std::move(item);
}

PoleType::PoleType Pole::getPoleType()
{
    return poleType;
}

void Pole::setPoleType(PoleType::PoleType poleType)
{
    this->poleType = poleType;
    setSymbol(poleType);
}

bool Pole::hasEntity()
{
    return entity != nullptr;
}

bool Pole::hasItem()
{
    return item != nullptr;
}

void Pole::removeEntity()
{
    if (hasEntity()) entity.reset();
}

void Pole::removeItem()
{
    if (hasItem()) item.reset();    
}

void Pole::draw()
{
    if (hasEntity()) 
    {
        entity->draw();
        return;
    }
    else if (hasItem) 
    {
        item->draw();
        return;
    }
    else
    {
        std::cout << symbol;
    }
}

char Pole::getSymbol()
{
    return symbol;
}   

bool Pole::isWalkable()
{
    return poleType != PoleType::PoleType::WALL;
}

void Pole::setSymbol(PoleType::PoleType poleType) 
{
    switch (poleType)
    {
        case PoleType::PoleType::FLOOR:
            symbol = ' ';
            break;
        case PoleType::PoleType::WALL:
            symbol = char(178);
            break;
    }
}