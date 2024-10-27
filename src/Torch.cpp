#include "Torch.hpp"
#include <iostream>

Torch::Torch(std::string name, int weight, bool isUsable, char symbol, int x, int y)
    : Item(name, weight, isUsable, symbol, x, y)
{

}

void Torch::use()
{
    //TODO: implement
}

void Torch::draw() const
{
    std::cout << getSymbol();
}

bool Torch::canBePlacedOn(TileType::TileType tileType) const
{
    return tileType == TileType::TileType::WALL;
}