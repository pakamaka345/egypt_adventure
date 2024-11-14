#pragma once
#include "items/Item.hpp"

class Torch : public Item
{
public:
    Torch(std::string name, int weight, bool isUsable, char symbol, int x, int y);
    ~Torch() = default;

    void use() override;
    void draw() const override;

    bool canBePlacedOn(TileType::TileType tileType) const override;

private:

};