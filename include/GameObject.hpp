#pragma once
#include "TileType.hpp"

class GameObject
{
public: 
    GameObject(int x, int y) : posX(x), posY(y) {}
    virtual ~GameObject() = default;    

    virtual void draw() const = 0;

    int getX() const { return posX; }
    int getY() const { return posY; }

    void setPos(int x, int y) { posX = x; posY = y; }

    virtual bool canBePlacedOn(TileType::TileType tileType) const = 0;

protected:
    int posX;
    int posY;
};