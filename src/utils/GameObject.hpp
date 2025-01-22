#pragma once
#include <valarray>
#include <functional>

#include "tiles/TileType.hpp"

struct Position {
    int x;
    int y;
    int z; // for indexing levels

    Position() : x(0), y(0), z(0) {}
    Position(const int x, const int y) : x(x), y(y), z(0) {}
    Position(const int x, const int y, const int z) : x(x), y(y), z(z) {}
    Position(Position const& pos) = default;

    Position& operator=(Position const& pos) = default;
    bool operator<(const Position& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    bool operator!=(const Position& other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    Position operator+(const Position& other) const {
        if (z != other.z) return { x + other.x, y + other.y, z + other.z };
        return {x + other.x, y + other.y, z};
    }

    Position operator-(const Position& other) const {
        if (z != other.z) return { x - other.x, y - other.y, z - other.z };
        return {x - other.x, y - other.y, z};
    }

    static Position abs(const Position& pos) {
        return { std::abs(pos.x), std::abs(pos.y), std::abs(pos.z) };
    }
};


namespace std
{
    template <>
    struct hash<Position>
    {
        std::size_t operator()(const Position& pos) const
        {
            using std::size_t;
            using std::hash;

            return ((hash<int>()(pos.x) ^ (hash<int>()(pos.y) << 1)) >> 1 ^ (hash<int>()(pos.z) << 1));
        }
    };
}


class GameObject
{
public: 
    GameObject(const int x, const int y, const int z, const char symbol) : posX(x), posY(y), posZ(z), symbol(symbol) {}
    virtual ~GameObject() = default;

    [[nodiscard]] int getX() const { return posX; }
    [[nodiscard]] int getY() const { return posY; }
    [[nodiscard]] int getZ() const { return posZ; }
    [[nodiscard]] Position getPos() const { return {posX, posY, posZ}; }
    [[nodiscard]] char getSymbol() const { return symbol; }

    void setPos(const int x, const int y, const int z) { posX = x; posY = y; posZ = z; }
    void setPos(const int x, const int y) { posX = x; posY = y; }
    void setPos(Position const& pos) { posX = pos.x; posY = pos.y; posZ = pos.z; }
    void setX(int x) { posX = x; }
    void setY(int y) { posY = y; }
    void setZ(int z) { posZ = z; }
    void setSymbol(char s) { symbol = s; }

protected:
    int posX;
    int posY;
    int posZ;
    char symbol;
};