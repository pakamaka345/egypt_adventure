#pragma once
#include "tiles/TileType.hpp"

struct Position {
    int x;
    int y;

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
    Position(Position const& pos) = default;

    Position& operator=(Position const& pos) = default;
    bool operator<(const Position& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Position& other) const {
        return x != other.x || y != other.y;
    }
};

class GameObject
{
public: 
    GameObject(int x, int y, char symbol) : posX(x), posY(y), symbol(symbol) {}
    virtual ~GameObject() = default;

    [[nodiscard]] int getX() const { return posX; }
    [[nodiscard]] int getY() const { return posY; }
    [[nodiscard]] char getSymbol() const { return symbol; }

    void setPos(int x, int y) { posX = x; posY = y; }
    void setPos(Position const& pos) { posX = pos.x; posY = pos.y; }
    void setX(int x) { posX = x; }
    void setY(int y) { posY = y; }
    void setSymbol(char s) { symbol = s; }

protected:
    int posX;
    int posY;
    char symbol;
};