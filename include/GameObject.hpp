#pragma once
#include "tiles/TileType.hpp"

class GameObject
{
public: 
    GameObject(int x, int y, char symbol) : posX(x), posY(y), symbol(symbol) {}
    virtual ~GameObject() = default;

    [[nodiscard]] int getX() const { return posX; }
    [[nodiscard]] int getY() const { return posY; }
    [[nodiscard]] char getSymbol() const { return symbol; }

    void setPos(int x, int y) { posX = x; posY = y; }
    void setX(int x) { posX = x; }
    void setY(int y) { posY = y; }
    void setSymbol(char s) { symbol = s; }

protected:
    int posX;
    int posY;
    char symbol;
};